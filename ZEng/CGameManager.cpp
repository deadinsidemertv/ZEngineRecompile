#include "CGameManager.h"
#include "oGameSession.h"
#include "oCMenu_ChgKeys.h"
#include "Globals.h"
#include "oCMenuSavegame.h"
#include "SystemFunc.h"
#include "zCMenu.h"


CGameManager::CGameManager() {}


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


	SystemFunc::sysEvent();
	SystemFunc::GameInit(this);
	SystemFunc::sysEvent();

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
		SystemFunc::Menu(this, 0);
		zCMenu::inGameMenu = 1;

		localExitFlag = this->exitFlag;
	}
};
void CGameManager::Done() {}

void CGameManager::InitScreen_Open()
{
	if (this->initScreen != nullptr) 
	{
		this->initScreen->Close(1); 
		this->initScreen = nullptr;
	}

	this->initScreen = new zCView(0, 0, 0x2000, 0x2000, 2);
	if (g_screen != nullptr) {
		g_screen->InsertItem(this->initScreen, 0);
	}
};