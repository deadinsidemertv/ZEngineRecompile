#include "Globals.h"
#include "zCEngine.h"
#include <ddraw.h>
#include "CGameManager.h"
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

int g_vidResetPaletteOnRestore = 0;

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

int g_vidModeFlag = 0;
SURFACE* g_Surfaces[3] = {};

int g_DAT_0086ebb8 = 0;

DirectDrawErrorEntry g_DirectDrawErrors[96] = {
    { (HRESULT)0x88760005, "Already initialized" },
    { (HRESULT)0x8876023E, "BltFast Can't Clip" },
    { (HRESULT)0x8876000A, "Surface can't be Attached" },
    { (HRESULT)0x88760014, "Surface can't be Detached" },
    { (HRESULT)0x88760249, "Can't Create DC" },
    { (HRESULT)0x88760247, "Can't Duplicate Surface" },
    { (HRESULT)0x88760280, "Can't Lock Page" },
    { (HRESULT)0x88760294, "Can't Unlock Page" },
    { (HRESULT)0x88760237, "Clipper is monitoring a HWND" },
    { (HRESULT)0x88760190, "No Color key set" },
    { (HRESULT)0x88760028, "Support is currently not available" },
    { (HRESULT)0x88760232, "DirectDraw object already created" },
    { (HRESULT)0x8876026C, "DC Already created" },
    { (HRESULT)0x88760037, "Exception occured" },
    { (HRESULT)0x88760245, "Exclusive mode is already set" },
    { (HRESULT)0x80004005, "Generic Failure" },
    { (HRESULT)0x8876005A, "H-Alignment Error" },
    { (HRESULT)0x8876023B, "HWND already set" },
    { (HRESULT)0x8876023A, "HWND is subclassed" },
    { (HRESULT)0x8876024C, "Can't restore implicit surface" },
    { (HRESULT)0x8876005F, "Incompatible primary buffer" },
    { (HRESULT)0x88760064, "Invalid Caps" },
    { (HRESULT)0x8876006E, "Invalid Cliplist" },
    { (HRESULT)0x88760231, "Invalid GUID" },
    { (HRESULT)0x88760078, "Invalid Display mode" },
    { (HRESULT)0x88760082, "Invalid Object" },
    { (HRESULT)0x80070057, "Invalid Parms" },
    { (HRESULT)0x88760091, "Invalid PixelFormat" },
    { (HRESULT)0x88760243, "Invalid Position" },
    { (HRESULT)0x88760096, "Invalid Rectangle" },
    { (HRESULT)0x88760250, "Invalid Surface Type" },
    { (HRESULT)0x887600A0, "Locked surface" },
    { (HRESULT)0x887600AA, "No 3D" },
    { (HRESULT)0x887600B4, "No Alpha hardware" },
    { (HRESULT)0x8876023F, "No Blitter hardware" },
    { (HRESULT)0x88760238, "No Clipper attached" },
    { (HRESULT)0x887600CD, "No cliplist" },
    { (HRESULT)0x887600D2, "No color conversion hardware" },
    { (HRESULT)0x887600D7, "No color key" },
    { (HRESULT)0x887600DC, "No hardware color key" },
    { (HRESULT)0x887600D4, "No Cooperative level set" },
    { (HRESULT)0x8876024A, "No DC for surface" },
    { (HRESULT)0x88760240, "No DirectDraw ROP hardware" },
    { (HRESULT)0x88760233, "No DirectDraw hardware" },
    { (HRESULT)0x887600DE, "No DirectDraw support currently" },
    { (HRESULT)0x88760235, "No emulation available" },
    { (HRESULT)0x887600E1, "No exclusive mode" },
    { (HRESULT)0x887600E6, "No page flip support" },
    { (HRESULT)0x887600F0, "No GDI present" },
    { (HRESULT)0x88760239, "No HWND for cooperation" },
    { (HRESULT)0x887600FA, "No mirror hardware" },
    { (HRESULT)0x88760242, "No overlay destination" },
    { (HRESULT)0x88760104, "No overlay hardware" },
    { (HRESULT)0x8876023C, "No palette attached" },
    { (HRESULT)0x8876023D, "No palette hardware" },
    { (HRESULT)0x88760118, "No ROP hardware" },
    { (HRESULT)0x88760122, "No rotation hardware" },
    { (HRESULT)0x88760136, "No stretching hardware" },
    { (HRESULT)0x88760140, "Not an 8 bit mode" },
    { (HRESULT)0x88760244, "Not an overlay surface" },
    { (HRESULT)0x8876014A, "No texture hardware" },
    { (HRESULT)0x88760246, "Not flippable" },
    { (HRESULT)0x887600FF, "Item was not found" },
    { (HRESULT)0x800401F0, "Not initialized" },
    { (HRESULT)0x88760248, "Not locked" },
    { (HRESULT)0x887602A8, "Page not locked" },
    { (HRESULT)0x8876024D, "Not palettized" },
    { (HRESULT)0x8876014F, "No VSYNC hardware" },
    { (HRESULT)0x88760154, "No hardware Z buffer" },
    { (HRESULT)0x8876015E, "No hardware Z overlay" },
    { (HRESULT)0x88760168, "Out of Caps" },
    { (HRESULT)0x8007000E, "Out of Memory" },
    { (HRESULT)0x8876017C, "Out of Video Memory" },
    { (HRESULT)0x8876017E, "No clip overlay support" },
    { (HRESULT)0x88760180, "Only one color key for overlay" },
    { (HRESULT)0x88760241, "Overlay hidden" },
    { (HRESULT)0x88760183, "Palette busy" },
    { (HRESULT)0x88760234, "Primary surface already exists" },
    { (HRESULT)0x88760236, "Region for clipper too small" },
    { (HRESULT)0x8876019A, "Surface already attached" },
    { (HRESULT)0x887601A4, "Surface already dependant" },
    { (HRESULT)0x887601AE, "Surface busy" },
    { (HRESULT)0x887601B8, "Surface obscured" },
    { (HRESULT)0x887601C2, "Surface lost" },
    { (HRESULT)0x887601CC, "Surface not attached" },
    { (HRESULT)0x887601D6, "Height is too big" },
    { (HRESULT)0x887601E0, "Size is too big" },
    { (HRESULT)0x887601EA, "Width is too big" },
    { (HRESULT)0x80004001, "Unsupported action" },
    { (HRESULT)0x887601FE, "Unsupported FOURCC format" },
    { (HRESULT)0x8876024E, "Unsupported mode" },
    { (HRESULT)0x88760208, "Unsupported mask" },
    { (HRESULT)0x88760219, "Vertical blank in progress" },
    { (HRESULT)0x8876021C, "DirectDraw still drawing" },
    { (HRESULT)0x8876024B, "Wrong mode" },
    { (HRESULT)0x88760230, "X-Alignment error" },
};

int g_sysExiting = 0;

CGameManager* g_gameMan = nullptr;

zCObjectFactory* g_zfactory = nullptr;

zCOption* g_zoption = nullptr;
zCMallocGeneric* g_zmalloc = nullptr;
zCResourceManager* g_zresMan = nullptr;
zERROR* g_zerr = nullptr;
zCFPUControler* g_zfpuControler = nullptr;