#include "SystemFunc.h"
#include "Globals.h"
#include "zCEngine.h"
#include "CGameManager.h"

void SystemFunc::sysEvent()
{
	if (g_SysEventInProgress) {
		return;
	}
	g_SysEventInProgress = true;

	if (g_TimerCallback != nullptr)
	{
		DWORD currentTime = 0;
		if (g_UseHighResTimer == 0) {
			currentTime = timeGetTime();
		}
		else {
			LARGE_INTEGER currentTick;
			QueryPerformanceCounter(&currentTick);
			currentTime = (DWORD)(currentTick.QuadPart / g_TimerFrequencyMS);
		}

		DWORD timeDelta = currentTime - g_GameTime;

		// Здесь в оригинале цикл, который вызывает коллбэк. 
		// Пока оставим просто вызов, чтобы не усложнять.
		if (timeDelta > (DWORD)(g_TimerAccumulator + g_TimerStep)) {
			g_TimerCallback(g_TimerAccumulator);
		}
	}

	MSG msg;

	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	if (!g_WaitScreenUnblank) {
		if (g_LostFocus /* || vidLostFocus() */) {
			// TODO: vidToggleFullScreenMode();
		}
	}
	else {
		// TODO: vidWaitScreenUnblank();
	}
	g_LostFocus = false;
	g_WaitScreenUnblank = false;

	if (g_RestoreCursor && GetActiveWindow() == g_HWND) {
		g_RestoreCursor = false;
		// TODO: Вызов метода рендерера (zrenderer + 0x110)
		// if (zrenderer) zrenderer->RestoreCursor(0);
	}

	g_SysEventInProgress = false;
}

void SystemFunc::sysParseCommandLine(char  *lpCmdLine)
{

}

void SystemFunc::sysHardExit(const char* msg,...)
{

}

void SystemFunc::NetInit()
{

}

void SystemFunc::cfgFetchTopic(const char* path) 
{

}

void SystemFunc::libExit() 
{

}

DWORD SystemFunc::LoaderThreadProc(LPVOID lpParam)
{
	g_DialogParam = CreateDialogParamA(g_hInstApp, (LPCSTR)0xa5, NULL, &SplashDlgProc, 0);
	SetWindowTextA(g_DialogParam, "Gothic Loading");

	if (g_DialogParam != nullptr)
	{
		HWND hWnd = GetDlgItem(g_DialogParam, 0x436);
		if (hWnd != nullptr) 
		{
			int splashW = g_SplashWidth;    
			int splashH = g_SplashHeight;   

			int x = (GetSystemMetrics(SM_CXSCREEN) - splashW) / 2;
			int y = (GetSystemMetrics(SM_CYSCREEN) - splashH) / 2;

			SetWindowPos(g_DialogParam, HWND_TOPMOST, x, y, splashW, splashH, SWP_SHOWWINDOW);
			// сразу снять «поверх всех»
			SetWindowPos(g_DialogParam, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

			// поставить картинку в Static-контрол
			SendMessageA(hWnd, STM_SETIMAGE, 0, (LPARAM)g_BitMap);

			UpdateWindow(g_DialogParam);

			// цикл сообщений — крутится, пока SplashDlgProc не вызовет PostQuitMessage
			MSG msg;
			while (GetMessageA(&msg, nullptr, 0, 0) != 0) {
				DispatchMessageA(&msg);
			}
		}
	}
	return 0;
}

INT_PTR SystemFunc::SplashDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);
	}
	return 0;
}

void SystemFunc::Menu(CGameManager* gm, int mode)
{

}

void SystemFunc::GameInit(CGameManager* gm)
{
	BYTE keyState[256];

	g_BitMap = LoadBitmapA(g_hInstApp, (LPCSTR)0xa9);

	g_LoaderThread = CreateThread(NULL, 0, &LoaderThreadProc, NULL, 0, &g_LoaderThreadId);
	GetKeyboardState(keyState);

	if ((keyState[VK_NUMLOCK] & 1) != 0) {
		keybd_event(VK_NUMLOCK, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_NUMLOCK, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	g_zEngine = new zCEngine();

	g_zEngine->Init(&gm->window);

	if (g_LoaderThreadId != 0) {
		PostThreadMessageA(g_LoaderThreadId, WM_QUIT, 0, 0);
	}

	sysEvent();
	gm->InitScreen_Open();

}


