#pragma once
#include <Windows.h>


DWORD sysGetTime();

void sysHardExit(const char* msg, ...);
void vidCloseDisplay(int needClose);