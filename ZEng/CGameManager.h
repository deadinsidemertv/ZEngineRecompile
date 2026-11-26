#pragma once
#include <windows.h>
#include "zCInputCallback.h"

class oGameSession;
class oCMenu_ChgKeys;
class oCMenuSavegame;
class zCView;

/// <summary>
/// 140byte class
/// </summary>

class CGameManager : public zCInputCallback
{
public:
	CGameManager();

	void Init(HWND hwnd);
	void Run();
	void Done();

	void GameInit();

	void InitScreen_Open();

	HWND window;
	oGameSession* gameSession = nullptr;

	void* saveGameManager = nullptr;

	zCView* initScreen = nullptr;

	oCMenu_ChgKeys* menuChgKeys = nullptr;
	oCMenuSavegame* menuSave = nullptr;
	oCMenuSavegame* menuLoad = nullptr;


	int exitFlag = 0;
	int menuInitialized = 0;
	


	void* field_0x64;
};



