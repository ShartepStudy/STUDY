#define __MYDLL__
#include "WH_HOOK.h"
#include "stdio.h"

#pragma warning (disable:4996)

HHOOK hHook; 
HINSTANCE hMod;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

bool installhook ()
{
	return hHook = SetWindowsHookEx(WH_MOUSE, MouseProc, hMod, 0);
}

bool removehook ()
{
	return UnhookWindowsHookEx(hHook);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ((nCode == HC_ACTION) && (wParam == WM_MOUSEMOVE))
	{
		MOUSEHOOKSTRUCT * mouse = (MOUSEHOOKSTRUCT *)lParam;
		FILE * pFile;
		pFile = fopen("hook.txt", "a+");
		if (pFile)
		{
			char str[300];
			sprintf(str, "%d  %d\n", mouse->pt.x, mouse->pt.y);
			fputs(str, pFile);
			fclose(pFile);
		}
		return 0;
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		hMod = (HINSTANCE)hModule;
	}
	return TRUE;
}
