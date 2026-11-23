#pragma once
#include <Windows.h>

struct SURFACE;

void vidMinimize(int restoreVideo);
void vidRestore();

int ddCheck(HRESULT result);

void FUN_004f19f0();
void FUN_004f1220(SURFACE* surf);