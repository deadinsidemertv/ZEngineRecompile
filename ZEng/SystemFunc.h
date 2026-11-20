#pragma once
#include <Windows.h>

class CGameManager;

class SystemFunc
{
public:
	static void sysEvent();
	static void sysParseCommandLine(char* lpCmdLine);
	static void sysHardExit(const char* msg,...);
	static void NetInit();
	static void cfgFetchTopic(const char* path);
	static void libExit();


	static DWORD LoaderThreadProc(LPVOID lpParam);
	static INT_PTR SplashDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

	static void Menu(CGameManager* gm, int mode);
	static void GameInit(CGameManager* gm);

	
};

