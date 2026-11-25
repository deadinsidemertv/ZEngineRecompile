#pragma once
#include <Windows.h>
#include <ddraw.h>

// Предварительные объявления классов (чтобы не тянуть лишние .h)
class zCEngine;
class zCView;
class CGameManager;
class zCObjectFactory;

extern CGameManager* g_gameMan;

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

extern int g_vidResetPaletteOnRestore;

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

struct VIDMODE {
    DWORD width = 0;
    DWORD height = 0;
    DWORD bpp = 0;
    DWORD unk1 = 0;
    DWORD unk2 = 0;
    DWORD unk3 = 0;
    DWORD unk4 = 0;
    char type;         // 0x20: 4 = окно, 5 = полный экран, 0xFF = не выбран
    DWORD unk5 = 0;
    DWORD unk6 = 0;
};

extern VIDMODE g_VideoHwModeCur;   // 0x00838ab4


// Бывший VideoObject, объединён с SURFACE (гипотеза: это один и тот же тип)
struct SURFACE
{
    char pad_0000;

    IDirectDrawSurface7* surface;  // +0x28
    char pad_002C;

    int field_30;                  // +0x30, == 5 похоже на режим "полный экран"
    char pad_0034;

    int needsRestore;              // +0x3C, ставится в 1 перед Restore()

    SURFACE* prev;                 // +0x40
    SURFACE* next;                 // +0x44
};

extern SURFACE* g_SurfaceListHead;
extern SURFACE* g_Surfaces[3]; // 0x0086ebc0, hypothesis: тот же тип, что и элементы списка

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

extern int g_vidModeFlag;

extern int g_DAT_0086ebb8;

extern int g_sysExiting;

extern zCObjectFactory* g_zfactory;