#include "acc_dlg.h"

CAcceleratorsDlg* CAcceleratorsDlg::ptr = NULL;

CAcceleratorsDlg::CAcceleratorsDlg(void)
{
	ptr = this;
}

void CAcceleratorsDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd,0);
	DestroyWindow(hwnd);
	PostQuitMessage(0);
}

void CAcceleratorsDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR str1[300], str2[50];
	HMENU hMenu = GetMenu(hwnd);
	GetMenuString(hMenu, id, str2, 50, MF_BYCOMMAND);
	if(codeNotify == 1)
		_tcscpy(str1, TEXT("Пункт меню выбран с помощью акселератора\n"));
	else if(codeNotify == 0)
		_tcscpy(str1, TEXT("Пункт меню выбран при непосредственном обращении к меню\n"));
	_tcscat(str1, str2);
	MessageBox(hwnd, str1, TEXT("Меню и акселераторы"), MB_OK | MB_ICONINFORMATION);
}

BOOL CALLBACK CAcceleratorsDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}