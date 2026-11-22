#include "zVideo_Win32.h"
#include "zWin32.h"
#include "SystemFunc.h"
#include <ddraw.h>
#include "Globals.h"

void vidMinimize(int restoreVideo)
{
	IDirectDraw7* g_DirectDraw;

	g_vidBusyMode = g_vidBusyMode | 1;

	DWORD time = (DWORD)sysGetTime();
	g_winMinimized = 1;

	if (g_DirectDraw != nullptr && g_VideoHwModeCur.type == 5) {
		ShowWindow(g_HWND, 0);
		SetWindowLongA(g_HWND, -0x14, 0x300);
		
		HRESULT result = g_DirectDraw->SetCooperativeLevel(g_HWND, 8);
		if (result != 0 && g_vidDontShowErrors == 0) 
		{
			const char* error;
			for (int i = 0; i < 0x60; ++i) {
				if (g_DirectDrawErrors[i].code == result)
					break;

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
	}

	if (restoreVideo != 0) {
		winWaitMessage(0x112, 0xf120, 0xfff0, 0, 0, 1);
		g_vidBusyMode = g_vidBusyMode | 2;
		if (g_VideoHwModeCur.type == 5) {
			SetWindowLongA(g_HWND, -0x14, 8);
			ShowWindow(g_HWND, 9);
		}
	}

	SURFACE* surfPtr = g_SurfaceListHead;
	if (g_DirectDraw != nullptr && g_VideoHwModeCur.type == 5) 
	{
		DWORD flags = 0x11;

		if (DAT_0086eb9c == 0) {
			flags = 0x13;
		}

	}
}
