#include "Globals.h"
#include "zCEngine.h"
#include "zCView.h"

HWND g_HWND = nullptr;
HINSTANCE g_hInstApp = nullptr;
const char* APP_NAME = "Gothic";

HANDLE g_lpTargetHandle = nullptr;
HANDLE g_FirstMutex = nullptr;

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

void* g_GDIObjects[99] = { nullptr };
HDC g_dcScreen = nullptr;

int g_WindowExtraWidth = 0;
int g_WindowExtraHeight = 0;
int g_WindowPosition = 0;
int g_WindowWidht = 0;
int g_WindowHeight = 0;
int g_VidHideMenu = 0;

const char* s_Could_not_register_window_class_00839c74 = "Could not register window class";

int g_UseRegistry = 0;
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