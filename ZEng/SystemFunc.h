#pragma once
#include <Windows.h>

class CGameManager;


void sysEvent();
void sysParseCommandLine(char* lpCmdLine);
void sysHardExit(const char* msg,...);
void NetInit();
void cfgFetchTopic(const char* path);
void libExit();


DWORD LoaderThreadProc(LPVOID lpParam);
INT_PTR SplashDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

void Menu(CGameManager* gm, int mode);
void GameInit(CGameManager* gm);


void CheckWindowsVersion();

INT_PTR CALLBACK MemoryDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	
int sysCheckOption(char* cmdLower, const char* option, bool remove);

void winWaitMessage(UINT message, WPARAM wParamValue, WPARAM wParamMask, LPARAM lParamValue, LPARAM lParamMask, BOOL checkWindowState);



