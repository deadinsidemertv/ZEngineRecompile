#include <iostream>
#include "SystemFunc.h"
#include "Globals.h"
#include <commctrl.h>
#include "CGameManager.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")

#define TARGET_FPS 70
#define TARGET_MS 0xe

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MainProg();


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow) {

    LARGE_INTEGER CurrentTick;

    g_hInstApp = hInstance;
    std::string lockName = "Lock_Gothic";
    HANDLE lockApp = CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 32, lockName.c_str());

    if (lockApp) {
        DWORD ErrorNum = GetLastError();
        if (ErrorNum == ERROR_ALREADY_EXISTS)
            ExitProcess(1);
    }

    DWORD winMainThreadID = GetCurrentThreadId();
    HANDLE hTargetProcessHandl = GetCurrentProcess();
    HANDLE hSourceHandl = GetCurrentThread();
    HANDLE hSourceProcessHandle = GetCurrentProcess();

    DuplicateHandle(hSourceProcessHandle, hSourceHandl, hTargetProcessHandl, &g_lpTargetHandle, 0, 0, DUPLICATE_SAME_ACCESS);

    QueryPerformanceFrequency((LARGE_INTEGER*)&g_TimerFrequencyLow);

    if (g_TimerFrequencyLow < 1000 || g_TimerFrequencyHigh != 0) {
        g_UseHighResTimer = 0;
        g_GameTime = timeGetTime();
    }
    else {
        g_TimerFrequencyMS = g_TimerFrequencyLow / 1000;
        g_TargetFPS_Ticks = g_TimerFrequencyLow / TARGET_FPS;
        g_UseHighResTimer = 1;
        QueryPerformanceCounter(&CurrentTick);
        g_GameTime = (DWORD)(CurrentTick.QuadPart / g_TimerFrequencyMS);
        CurrentTick.LowPart = g_GameTime;
    }

    if (g_UseHighResTimer == 0) {
        g_EngineTick = timeGetTime();
        g_EngineTick = g_EngineTick / TARGET_MS;
    }
    else {
        QueryPerformanceCounter(&CurrentTick);
        g_EngineTick = (DWORD)(CurrentTick.QuadPart / g_TargetFPS_Ticks);
        CurrentTick.LowPart = g_EngineTick;
    }

    SystemFunc::sysParseCommandLine(lpCmdLine);
    g_FirstMutex = CreateMutexA(NULL, FALSE, NULL);
    GetModuleFileNameA(NULL,g_ExePath, MAX_PATH);
    InitCommonControls();

    memset(g_GDIObjects, 0, sizeof(g_GDIObjects));

    g_dcScreen = CreateCompatibleDC(NULL);
    int tempMetric = GetSystemMetrics(SM_CXFRAME);
    g_WindowExtraWidth = tempMetric * 2 + 5;
    tempMetric = GetSystemMetrics(SM_CYFRAME);
    int captionHeight = GetSystemMetrics(SM_CYCAPTION);
    g_WindowExtraHeight = captionHeight + 5 + tempMetric * 2;
    if (g_VidHideMenu == 0) {
        tempMetric = GetSystemMetrics(SM_CYMENU);
        g_WindowExtraHeight = g_WindowExtraHeight + tempMetric;
    }

    WNDCLASSA windowClass = { 0 };
    g_Menu = CreateMenu();
    g_Icon = LoadIconA(g_hInstApp, (LPCSTR)MAKEINTRESOURCE(102));
    windowClass.style = 3;
    windowClass.lpfnWndProc = &WindowProc;
    windowClass.hInstance = g_hInstApp;
    windowClass.lpszClassName = "DDWndClass";
    windowClass.hIcon = g_Icon;
    ATOM WindowClassID = RegisterClassA(&windowClass);

    if (WindowClassID == 0) {
        SystemFunc::sysHardExit(s_Could_not_register_window_class_00839c74);
    }

    g_WindowPosition = CW_USEDEFAULT;
    g_WindowWidht = g_WindowExtraWidth + 320;
    g_WindowHeight = g_WindowExtraHeight + 240;

    if (g_UseRegistry != 0) {
        SystemFunc::cfgFetchTopic("error");
    }

    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    if (g_IsWindowVisible != 0) {
        dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    }

    g_HWND = CreateWindowExA(0x300, "DDWndClass", APP_NAME, dwStyle, g_WindowPosition, g_WindowPosition,g_WindowWidht, g_WindowHeight, NULL, g_Menu, g_hInstApp, NULL);

    if (g_HWND != nullptr) {

        ShowWindow(g_HWND, SW_SHOW); // Принудительно показываем окно
        UpdateWindow(g_HWND);

        SystemFunc::NetInit();
        MainProg();
        SystemFunc::libExit();
    }

    return 0;
}


int MainProg()
{

    SystemFunc::sysEvent();

    CGameManager GameManager;
    GameManager.Init(g_HWND);
    GameManager.Run();
    GameManager.Done();

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}