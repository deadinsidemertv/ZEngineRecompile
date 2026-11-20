#pragma once
#include <windows.h>

class oGameSession;
class oCMenu_ChgKeys;
class oCMenuSavegame;
class zCView;



class CGameManager
{
public:
	CGameManager();

	void Init(HWND hwnd);
	void Run();
	void Done();

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



