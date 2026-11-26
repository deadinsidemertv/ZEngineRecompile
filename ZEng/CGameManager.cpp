#include "CGameManager.h"
#include "oGameSession.h"
#include "oCMenu_ChgKeys.h"
#include "Globals.h"
#include "zCView.h"
#include "zCEngine.h"
#include "oCMenuSavegame.h"
#include "SystemFunc.h"
#include "zCMenu.h"


CGameManager::CGameManager() 
{
	g_gameMan = this;

}

void CGameManager::GameInit()
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

	g_zEngine->Init(&window);

	if (g_LoaderThreadId != 0) {
		PostThreadMessageA(g_LoaderThreadId, WM_QUIT, 0, 0);
	}

	sysEvent();
	InitScreen_Open();
}


void CGameManager::Init(HWND hwnd) 
{
	this->window = hwnd;

	if (this->field_0x64 != nullptr) {
		// TODO: уточнить тип и метод
		this->field_0x64 = nullptr;
	}

	if (this->gameSession != nullptr) {
		delete this->gameSession;   
	}
	this->gameSession = nullptr;


	sysEvent();
	GameInit();
	sysEvent();

};


void CGameManager::Run() 
{
	if (this->menuInitialized == 0) 
	{
		this->exitFlag = 0;

		this->menuChgKeys = new oCMenu_ChgKeys("MENU_CHG_KEYS");

		this->menuSave = new oCMenuSavegame("MENU_SAVE", 0);

		this->menuLoad = new oCMenuSavegame("MENU_LOAD", 1);

		if (this->menuSave != nullptr) {
			((oCMenuSavegame*)this->menuSave)->saveManager = this->saveGameManager;
		}
		if (this->menuLoad != nullptr) {
			((oCMenuSavegame*)this->menuLoad)->saveManager = this->saveGameManager;
		}


		this->menuInitialized = 1;
	}

	oGameSession* session = (oGameSession*)this->gameSession;
	int localExitFlag = this->exitFlag;

	while ((localExitFlag == 0 && (session == nullptr || (localExitFlag = session->Update()) == 0)))
	{
		zCMenu::inGameMenu = 0;
		Menu(this, 0);
		zCMenu::inGameMenu = 1;

		localExitFlag = this->exitFlag;
	}
};
void CGameManager::Done() {}

void CGameManager::InitScreen_Open()
{
	if (initScreen != nullptr) 
	{
		initScreen->Close(1); 
		initScreen = nullptr;
	}

	initScreen = new zCView(0, 0, 0x2000, 0x2000, 2);
	if (g_screen != nullptr) {
		g_screen->InsertItem(initScreen, 0);
	}
};