#include "menu_dlg.h"

#define ID_FILE_EXIT WM_USER
#define ID_EDIT_DELETE WM_USER+1
#define ID_EDIT_FINDNEXT WM_USER+2
#define ID_EDIT_TIMEDATE WM_USER+3
#define ID_EDIT_GOTO WM_USER+4
#define ID_VIEW_STATUSBAR WM_USER+5
#define ID_FILE_NEW WM_USER+6
#define ID_FILE_OPEN WM_USER+7
#define ID_FILE_SAVE WM_USER+8
#define ID_FILE_SAVE_AS WM_USER+9
#define ID_FILE_PAGE_SETUP WM_USER+10
#define ID_FILE_PRINT WM_USER+11
#define ID_EDIT_UNDO WM_USER+12
#define ID_EDIT_CUT WM_USER+13
#define ID_EDIT_COPY WM_USER+14
#define ID_EDIT_PASTE WM_USER+15
#define ID_EDIT_FIND WM_USER+16
#define ID_EDIT_REPLACE WM_USER+17
#define ID_EDIT_SELECT_ALL WM_USER+18

CMenuBarDlg* CMenuBarDlg::ptr = NULL;

CMenuBarDlg::CMenuBarDlg(void)
{
	ptr = this;
}

void CMenuBarDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMenuBarDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	HMENU subFileMenu = CreatePopupMenu();
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_NEW, TEXT("New"));
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_OPEN, TEXT("Open..."));
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_SAVE, TEXT("Save"));
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_SAVE_AS, TEXT("Save As..."));
	AppendMenu(subFileMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_PAGE_SETUP, TEXT("Page Setup..."));
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_PRINT, TEXT("Print..."));
	AppendMenu(subFileMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(subFileMenu, MF_STRING, ID_FILE_EXIT, TEXT("Exit"));
	HMENU subEditMenu = CreatePopupMenu();
	AppendMenu(subEditMenu, MF_STRING | MF_GRAYED, ID_EDIT_UNDO, TEXT("Undo"));
	AppendMenu(subEditMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(subEditMenu, MF_STRING | MF_GRAYED, ID_EDIT_CUT, TEXT("Cut"));
	AppendMenu(subEditMenu, MF_STRING | MF_GRAYED, ID_EDIT_COPY, TEXT("Copy"));
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_PASTE, TEXT("Paste"));
	AppendMenu(subEditMenu, MF_STRING | MF_GRAYED, ID_EDIT_DELETE, TEXT("Delete"));
	AppendMenu(subEditMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_FIND, TEXT("Find... "));
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_FINDNEXT, TEXT("Find Next"));
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_REPLACE, TEXT("Replace..."));
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_GOTO, TEXT("Go To..."));
	AppendMenu(subEditMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_SELECT_ALL, TEXT("Select All"));
	AppendMenu(subEditMenu, MF_STRING, ID_EDIT_TIMEDATE, TEXT("Time/Date"));
	HMENU subViewMenu = CreatePopupMenu();
	AppendMenu(subViewMenu, MF_STRING | MF_CHECKED, ID_VIEW_STATUSBAR, TEXT("Status Bar"));
	HMENU mainMenu = CreateMenu();
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subFileMenu, TEXT("File"));
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subEditMenu, TEXT("Edit"));
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subViewMenu, TEXT("View"));
	SetMenu(hwnd, mainMenu);
	return TRUE;
}

// Обработчик сообщения WM_COMMAND будет вызван при выборе пункта меню
void CMenuBarDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HMENU hMenu = GetMenu(hwnd);
	TCHAR buf[30] = {0};
	GetMenuString(hMenu, id, buf, 30, MF_BYCOMMAND);
	MessageBox(hwnd, buf, TEXT("Динамическое создание меню"), MB_ICONINFORMATION | MB_OK);
}


BOOL CALLBACK CMenuBarDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}