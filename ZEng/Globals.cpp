#include "Globals.h"
#include "zCEngine.h"
#include <ddraw.h>
#include "zCView.h"

char* g_sysCommandLine = 0;
char* g_LogFileName = 0;

HWND g_HWND = nullptr;
HINSTANCE g_hInstApp = nullptr;
const char* APP_NAME = "Gothic";

HANDLE g_hMainThread = nullptr;
HANDLE g_FirstMutex = nullptr;
HANDLE g_lockApp = nullptr;

HMENU g_Menu = nullptr;
HICON g_Icon = nullptr;
HBITMAP g_BitMap = nullptr;

char g_ExePath[MAX_PATH] = { 0 };

DWORD g_TimerFrequencyLow = 0;
DWORD g_TimerFrequencyHigh = 0;
DWORD g_GameTime = 0;
DWORD g_UseHighResTimer = 0;
DWORD g_TimerFrequencyMS = 0;
DWORD g_TargetFPS_Ticks = 0;
DWORD g_EngineTick = 0;

DWORD g_SysTimeGap = 0;

DWORD g_winMainThreadID = 0;

DWORD g_MouseData[99] = { 0 };
HDC g_dcScreen = nullptr;

int g_WindowExtraWidth = 0;
int g_WindowExtraHeight = 0;
int g_WindowPosition = 0;
int g_WindowWidht = 0;
int g_WindowHeight = 0;
int g_VidHideMenu = 0;

int g_winBPP = 0;
int g_winNT = 0;

int g_usrSafeMode = 0;

const char* s_Could_not_register_window_class_00839c74 = "Could not register window class";

int g_UseRegistry = 1;  
int g_IsWindowVisible = 0;

HANDLE g_LoaderThread = nullptr;
DWORD  g_LoaderThreadId = 0;
HWND g_DialogParam = nullptr;
int g_SplashWidth = 0;
int g_SplashHeight = 0;

zCEngine* g_zEngine = nullptr;
zCView* g_screen = nullptr;

bool g_SysEventInProgress = false;
void (*g_TimerCallback)(int) = nullptr;
int g_TimerAccumulator = 0;
int g_TimerStep = 0;
bool g_WaitScreenUnblank = false;
bool g_LostFocus = false;
bool g_RestoreCursor = false;

VIDMODE g_VideoHwModeCur;

int g_netEnable = 0;
int g_safeLog = 0;
int g_windowed = 0;
int g_noNetwork = 0;
int g_noDraw = 0;
int g_noDrawwin = 0;
int g_vidCheckMemory = 0;

int g_vidBusyMode = 0;
int g_winMinimized = 0;

IDirectDraw7* g_DirectDraw = nullptr;
int g_vidDontShowErrors = 0;
const char* g_DirectDrawError = 0;
SURFACE* g_SurfaceListHead = nullptr;