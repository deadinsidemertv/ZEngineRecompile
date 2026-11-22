#include "SystemFunc.h"
#include "Globals.h"
#include "CGameManager.h"

int MainProg()
{

    sysEvent();

    CGameManager GameManager;
    GameManager.Init(g_HWND);
    GameManager.Run();
    GameManager.Done();

    return 0;
}