#pragma once
#include <Windows.h>

// Предварительные объявления классов (чтобы не тянуть лишние .h)
class zCEngine;
class zCView;

// --- Оконные хэндлы и приложение ---
extern HWND g_HWND;
extern HINSTANCE g_hInstApp;
extern const char* APP_NAME;

// --- Разное системное ---
extern HANDLE g_lpTargetHandle;
extern HANDLE g_FirstMutex;
extern HANDLE g_lockApp;
extern HMENU g_Menu;
extern HICON g_Icon;
extern HBITMAP g_BitMap;
extern char g_ExePath[MAX_PATH]; 
extern HDC g_dcScreen;
extern void* g_GDIObjects[99];

// --- Таймеры и FPS ---
extern DWORD g_TimerFrequencyLow;
extern DWORD g_TimerFrequencyHigh;
extern DWORD g_GameTime;
extern DWORD g_UseHighResTimer;
extern DWORD g_TimerFrequencyMS;
extern DWORD g_TargetFPS_Ticks;
extern DWORD g_EngineTick;

// --- Параметры окна ---
extern int g_WindowExtraWidth;
extern int g_WindowExtraHeight;
extern int g_WindowPosition;
extern int g_WindowWidht;
extern int g_WindowHeight;
extern int g_VidHideMenu;
extern int g_UseRegistry;
extern int g_IsWindowVisible;

// --- Строки/Константы ---
extern const char* s_Could_not_register_window_class_00839c74;

// --- Загрузчик и Сплэш-скрин ---
extern HANDLE g_LoaderThread;
extern DWORD  g_LoaderThreadId;
extern HWND g_DialogParam;
extern int g_SplashWidth;
extern int g_SplashHeight;

// --- Движок и Рендеринг ---
extern zCEngine* g_zEngine;
extern zCView* g_screen;

extern bool g_SysEventInProgress;
extern void (*g_TimerCallback)(int);
extern int g_TimerAccumulator;
extern int g_TimerStep;
extern bool g_WaitScreenUnblank;
extern bool g_LostFocus;
extern bool g_RestoreCursor;