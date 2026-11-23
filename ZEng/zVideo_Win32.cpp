#include "zVideo_Win32.h"
#include "zWin32.h"
#include "SystemFunc.h"
#include <ddraw.h>
#include "Globals.h"

int ddCheck(HRESULT result);

void vidMinimize(int restoreVideo)
{
	HRESULT result;

	g_vidBusyMode = g_vidBusyMode | 1;

	DWORD time = (DWORD)sysGetTime();
	g_winMinimized = 1;

	if (g_DirectDraw != nullptr && g_VideoHwModeCur.type == 5) 
	{
		ShowWindow(g_HWND, 0);
		SetWindowLongA(g_HWND, -0x14, 0x300);
		
		result = g_DirectDraw->SetCooperativeLevel(g_HWND, 8);
		if (result != 0 && g_vidDontShowErrors == 0) 
		{
			int i=0;
			for (; i < 0x60; ++i) {
				if (g_DirectDrawErrors[i].code == result)
					break;
			}

			if (i == 96)
			{
				g_DirectDrawError = "unknown error";
			}
			else
			{
				g_DirectDrawError = (char*)g_DirectDrawErrors[i].message;
			}
		}
		g_DirectDraw->FlipToGDISurface();
	}

	ShowWindow(g_HWND, 2);
	g_vidBusyMode = g_vidBusyMode & 0xfffffffe;
	g_DAT_0086ebb8 = 0;

	if (restoreVideo != 0) 
	{
		winWaitMessage(0x112, 0xf120, 0xfff0, 0, 0, 1);
		g_vidBusyMode = g_vidBusyMode | 2;

		if (g_VideoHwModeCur.type == 5) 
		{
			SetWindowLongA(g_HWND, -0x14, 8);
			ShowWindow(g_HWND, 9);
		}

		SURFACE* surfPtr = g_SurfaceListHead;

		if (g_DirectDraw != nullptr && g_VideoHwModeCur.type == 5)
		{
			DWORD flags = 0x11;

			if (g_vidModeFlag == 0) {
				flags = 0x13;
			}
			
			result = g_DirectDraw->SetCooperativeLevel(g_HWND, flags);
			if (result && g_vidDontShowErrors == 0) 
			{
				int i = 0;
				for (; i < 0x60; ++i) {
					if (g_DirectDrawErrors[i].code == result)
						break;
				}

				if (i == 96)
				{
					g_DirectDrawError = "unknown error";
				}
				else
				{
					g_DirectDrawError = (char*)g_DirectDrawErrors[i].message;
				}
			}

			HRESULT SetDisplayModeResult = g_DirectDraw->SetDisplayMode(g_VideoHwModeCur.width, g_VideoHwModeCur.height, g_VideoHwModeCur.bpp,0,0);
			ddCheck(SetDisplayModeResult);
			SURFACE* videoobject = g_Surfaces[0];

			if (videoobject->field_30 == 5)
			{
				IDirectDrawSurface7* surface = videoobject->surface;

				if (surface->IsLost() != 0)
				{
					videoobject->needsRestore = 1;
					HRESULT restoreResult = surface->Restore();
					ddCheck(restoreResult);
				}
			}

			FUN_004f19f0();

			for (; surfPtr != nullptr; surfPtr = surfPtr->next)
			{
				FUN_004f1220(surfPtr); // todo: check args
			}

			if (g_Surfaces[1] != nullptr)
			{
				FUN_004f1220(g_Surfaces[1]); // todo: check args
			}

			if (g_Surfaces[2] != nullptr)
			{
				FUN_004f1220(g_Surfaces[2]); // todo: check args
			}
		}
		if (g_vidResetPaletteOnRestore != 0)
		{
			HDC hdc = GetDC(g_HWND);
			SetSystemPaletteUse(hdc, 2);
			SetSystemPaletteUse(hdc, 1);
			ReleaseDC(g_HWND, hdc);
		}
		g_vidBusyMode = g_vidBusyMode & 0xfffffffd;
		g_winMinimized = 0;
	}
	DWORD curTime = sysGetTime();
	g_SysTimeGap = g_SysTimeGap + (curTime - time);
	return;
}

void vidRestore()
{
	HRESULT result;

	g_vidBusyMode = g_vidBusyMode | 2;
	if (g_VideoHwModeCur.type == 5) {
		SetWindowLongA(g_HWND, -0x14, 8);
		ShowWindow(g_HWND, 9);
	}

	SURFACE* surfPtr = g_SurfaceListHead;
	if (g_DirectDraw && g_VideoHwModeCur.type == 5) {
		DWORD flags = 0x11;
		if (g_vidModeFlag == 0) {
			flags = 0x13;
		}
		result =  g_DirectDraw->SetCooperativeLevel(g_HWND, flags);
		if (result && g_vidDontShowErrors == 0) {
			int i = 0;
			for (;i < 0x60;i++)
			{
				if (g_DirectDrawErrors[i].code == result) {
					break;
				}
			}

			if (i == 96) {
				g_DirectDrawError = "unknown error";
			}
			else {
				g_DirectDrawError = (char*)g_DirectDrawErrors[i].message;
			}
		}

		result = g_DirectDraw->SetDisplayMode(g_VideoHwModeCur.width, g_VideoHwModeCur.height, g_VideoHwModeCur.bpp, 0, 0);

		if (result && g_vidDontShowErrors == 0) {
			int i = 0;
			for (;i < 0x60;i++)
			{
				if (g_DirectDrawErrors[i].code == result) {
					break;
				}
			}

			if (i == 96) {
				g_DirectDrawError = "unknown error";
			}
			else {
				g_DirectDrawError = (char*)g_DirectDrawErrors[i].message;
			}
		}

		SURFACE* videoobject = g_Surfaces[0];

		if (videoobject->field_30 == 5)
		{
			IDirectDrawSurface7* surface = videoobject->surface;

			if (surface->IsLost() != 0)
			{
				videoobject->needsRestore = 1;
				HRESULT restoreResult = surface->Restore();
				ddCheck(restoreResult);
			}
		}
		FUN_004f19f0();

		for (; surfPtr != nullptr; surfPtr = surfPtr->next)
		{
			FUN_004f1220(surfPtr); // todo: check args
		}

		if (g_Surfaces[1] != nullptr)
		{
			FUN_004f1220(g_Surfaces[1]); // todo: check args
		}

		if (g_Surfaces[2] != nullptr)
		{
			FUN_004f1220(g_Surfaces[2]); // todo: check args
		}
	}
	if (g_vidResetPaletteOnRestore != 0) {
		HDC hdc = GetDC(g_HWND);
		SetSystemPaletteUse(hdc, 2);
		SetSystemPaletteUse(hdc, 1);
		ReleaseDC(g_HWND, hdc);
	}
	g_vidBusyMode = g_vidBusyMode & 0xfffffffd;
	g_winMinimized = 0;

	return;
}

int ddCheck(HRESULT result)
{
	if (result == 0) {
		return 1;
	}

	if (g_vidDontShowErrors == 0) 
	{
		int i = 0;
		for (;i < 0x60;i++) {
			if (g_DirectDrawErrors[i].code == result) {
				break;
			}
		}

		if (i == 0x60) {
			g_DirectDrawError = "unknown error";
			return 0;
		}
		
		g_DirectDrawError = (char*)g_DirectDrawErrors[i].message;
	}
	return 0;
}

void FUN_004f19f0()
{

}

void FUN_004f1220(SURFACE* surf)
{

}
