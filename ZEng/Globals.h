#pragma once
#include <Windows.h>
#include <ddraw.h>

// Предварительные объявления классов (чтобы не тянуть лишние .h)
class zCEngine;
class zCView;



extern char* g_sysCommandLine;
extern char* g_LogFileName;
// --- Оконные хэндлы и приложение ---
extern HWND g_HWND;
extern HINSTANCE g_hInstApp;
extern const char* APP_NAME;

// --- Разное системное ---
extern HANDLE g_hMainThread;
extern HANDLE g_FirstMutex;
extern HANDLE g_lockApp;
extern HMENU g_Menu;
extern HICON g_Icon;
extern HBITMAP g_BitMap;
extern char g_ExePath[MAX_PATH]; 
extern HDC g_dcScreen;
extern DWORD g_MouseData[99];

// --- Таймеры и FPS ---
extern DWORD g_TimerFrequencyLow;
extern DWORD g_TimerFrequencyHigh;
extern DWORD g_GameTime;
extern DWORD g_UseHighResTimer;
extern DWORD g_TimerFrequencyMS;
extern DWORD g_TargetFPS_Ticks;
extern DWORD g_EngineTick;

extern DWORD g_SysTimeGap;

extern DWORD g_winMainThreadID;

// --- Параметры окна ---
extern int g_WindowExtraWidth;
extern int g_WindowExtraHeight;
extern int g_WindowPosition;
extern int g_WindowWidht;
extern int g_WindowHeight;
extern int g_VidHideMenu;
extern int g_UseRegistry;
extern int g_IsWindowVisible;

// --- Флаги платформы ---
extern int g_winBPP;
extern int g_winNT;

extern int g_usrSafeMode;

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

#pragma pack(push, 1)
struct VIDMODE {
    char pad[0x20];    // поля 0x00-0x1F пока неизвестны
    char type;         // 0x20: 4 = окно, 5 = полный экран, 0xFF = не выбран
    char pad2[0x1B];   // добиваем до 60 байт (0x3C)
};
static_assert(sizeof(VIDMODE) == 60, "VIDMODE size");
#pragma pack(pop)

extern VIDMODE g_VideoHwModeCur;   // 0x00838ab4


/// флаги запуска из cmdLine

extern int g_netEnable;
extern int g_safeLog;
extern int g_windowed;
extern int g_noNetwork;
extern int g_noDraw;
extern int g_noDrawwin;
extern int g_vidCheckMemory;

extern int g_vidBusyMode;
extern int g_winMinimized;

extern IDirectDraw7* g_DirectDraw;
extern int g_vidDontShowErrors;

struct DirectDrawErrorEntry
{
    HRESULT code;
    const char* message;
};

extern DirectDrawErrorEntry g_DirectDrawErrors[96];
extern const char* g_DirectDrawError;
struct SURFACE
{
    // ...
    SURFACE* prev; // +0x40
    SURFACE* next; // +0x44
};

extern SURFACE* g_SurfaceListHead;