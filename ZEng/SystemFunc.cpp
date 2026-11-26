#include "SystemFunc.h"
#include "Globals.h"
#include "zCEngine.h"
#include "zVideo_Win32.h"
#pragma warning(disable : 4996)
#include "CGameManager.h"

void sysEvent()
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

void sysParseCommandLine(char  *lpCmdLine)
{
	char* buf = (char*)LocalAlloc(LMEM_ZEROINIT, strlen(lpCmdLine) + 2);

	if (buf == 0) {
		// Памяти не хватило. Пока показывается диалог, время игры не должно идти,
		// поэтому его замеряют до и после и разницу добавляют в g_SysTimeGap.
		DWORD CurrentTime;
		LARGE_INTEGER counter;

		if (g_UseHighResTimer == 0) {
			CurrentTime = timeGetTime();
		}
		else {
			QueryPerformanceCounter(&counter);
			CurrentTime = (DWORD)(counter.QuadPart / g_TimerFrequencyMS);
		}
		DWORD TimeFromStart = CurrentTime - g_GameTime;

		bool vidMode = (g_VideoHwModeCur.type == 5);
		if (vidMode) {
			vidMinimize(0);
		}
		buf = (char*)DialogBoxParamA(g_hInstApp, MAKEINTRESOURCEA(143), g_HWND,
			MemoryDialogProc, strlen(lpCmdLine) + 2);
		if (vidMode) {
			vidRestore();
		}

		if (g_UseHighResTimer == 0) {
			CurrentTime = timeGetTime();
		}
		else {
			QueryPerformanceCounter(&counter);
			CurrentTime = (DWORD)(counter.QuadPart / g_TimerFrequencyMS);
		}
		g_SysTimeGap = g_SysTimeGap + ((CurrentTime - g_GameTime) - TimeFromStart);

		if (buf == 0) {
			libExit();
			if (g_hMainThread != 0) CloseHandle(g_hMainThread);
			if (g_FirstMutex != 0) CloseHandle(g_FirstMutex);
			ExitProcess(0);
		}
	}

	g_sysCommandLine = buf;
	strcpy(buf, lpCmdLine);

	char cmdLower[2048];
	strcpy(cmdLower, lpCmdLine);
	_strlwr(cmdLower);

	char* logArg = strstr(cmdLower, "-log=");

	if (logArg != nullptr) {
		int pos = (int)(logArg - cmdLower);

		const char* src = g_sysCommandLine + pos + 5;
		int j = 0;

		while (src[j] != '\0' && src[j] != ' ') {
			g_LogFileName[j] = src[j];                  // 0x0086ed28
			j++;
		}
		g_LogFileName[j] = '\0';

		int consumed = j + 6;

		memmove(cmdLower + pos, cmdLower + pos + consumed, strlen(cmdLower) - pos);
		memmove(g_sysCommandLine + pos, g_sysCommandLine + pos + consumed,
			strlen(g_sysCommandLine) - pos);
	}

	int found;

	found = sysCheckOption(cmdLower, "-safe", 1);
	if (found != 0) {
		g_usrSafeMode = 1;
	}
	found = sysCheckOption(cmdLower, "-windowed", 1);
	if (found != 0) {
		g_windowed = 1;
	}
	found = sysCheckOption(cmdLower, "-fullscreen", 1);
	if (found != 0) {
		g_windowed = 2;
	}
	found = sysCheckOption(cmdLower, "-safelog", 1);
	if (found != 0) {
		g_safeLog = 1;
	}
	found = sysCheckOption(cmdLower, "-nonetwork", 1);
	if (found != 0) {
		g_netEnable = 0;
	}
	found = sysCheckOption(cmdLower, "-noddrawwin", 1);
	if (found != 0) {
		g_noDrawwin = 0;
	}
	found = sysCheckOption(cmdLower, "-noddraw", 1);
	if (found != 0) {
		g_noDraw = 0;
	}
	found = sysCheckOption(cmdLower, "-noddrawmemcheck", 1);
	if (found != 0) {
		g_vidCheckMemory = 0;
	}
	found = sysCheckOption(cmdLower, "-noreg", 1);
	if (found != 0) {
		g_UseRegistry = 0;
	}
	if (g_usrSafeMode != 0) {

		g_windowed = 4;
		g_netEnable = 0;
		g_noDraw = 0;
		g_noDrawwin = 0;
	}
	return;
}


void NetInit()
{

}

void cfgFetchTopic(const char* path) 
{

}

void libExit() 
{

}

void zInitOptions()
{

}

DWORD LoaderThreadProc(LPVOID lpParam)
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

INT_PTR SplashDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);
	}
	return 0;
}

void Menu(CGameManager* gm, int mode)
{

}


void CheckWindowsVersion()
{
	HDC hdc;
	char osName[64];

	OSVERSIONINFOA vi = {0};
	vi.dwOSVersionInfoSize = sizeof(vi);
	GetVersionExA(&vi);
	if (vi.dwPlatformId == 0) {
		MessageBoxA(g_HWND, "s_This_program_cannot_be_run_under", NULL, MB_ICONHAND | MB_SETFOREGROUND);
		_exit(3);
	}

	hdc = GetDC(NULL);
	g_winBPP = GetDeviceCaps(hdc, 0xc);
	ReleaseDC(NULL, hdc);
	if (g_winBPP < 8) {
		MessageBoxA(g_HWND,"s_This_program_requires_a_256_color", NULL, MB_ICONHAND | MB_SETFOREGROUND);
		_exit(2);
	}

	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {   // 1
		strcpy(osName, "Microsoft Windows");
	}
	else if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT) {   // 2
		strcpy(osName, "Microsoft Windows NT");
		g_winNT = 1;
	}
	else {
		strcpy(osName, "an unknown operating system");
	}

	for (const char* p = vi.szCSDVersion; *p != '\0'; p++) {
		if (*p != ' ' && *p != '\t') {
			strcat(osName, " ");
			strcat(osName, vi.szCSDVersion);
			break;
		}
	}

	return;
}



INT_PTR CALLBACK MemoryDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;   // TODO: FUN_004f34c0
}

int sysCheckOption(char* cmdLower, const char* option, bool remove)
{
	size_t len = strlen(option);                  // первый цикл с 0xffffffff
	char* found = strstr(cmdLower, option);

	while (found != nullptr) {
		char next = found[len];                   // символ сразу после ключа
		if (next == ' ' || next == '\t' || next == '\0') {   // ключ целое слово
			if (!remove)
				return true;

			size_t cut = len;                     // сколько символов вырезать
			if (next == ' ' || next == '\t')
				cut = len + 1;                    // вместе с пробелом после ключа

			// вырезаем из cmdLower
			memmove(found, found + cut, strlen(found + cut) + 1);

			// то же место в оригинальной строке
			char* inOrig = g_sysCommandLine + (found - cmdLower);
			memmove(inOrig, inOrig + cut, strlen(inOrig + cut) + 1);
			return true;
		}
		found = strstr(found + 1, option);        // не то слово, ищем дальше
	}
	return false;
}

void winWaitMessage(UINT message, WPARAM wParamValue, WPARAM wParamMask, LPARAM lParamValue, LPARAM lParamMask, BOOL checkWindowState)
{

}

INT_PTR CALLBACK FatalErrorDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// todo: оригинал FUN_004f62b0 рисует свой заголовок (ccDrawCaption), пока не переносим
	return 0;
}

