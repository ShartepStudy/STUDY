#include "context_menu_dlg.h"

static HBITMAP paHbm;

CContextMenuDlg* CContextMenuDlg::ptr = NULL;

CContextMenuDlg::CContextMenuDlg(void)
{
	ptr = this;
	dwButtonState = dwEditState = dwCheckboxState = MF_CHECKED;
}

void CContextMenuDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CContextMenuDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	// дескрипторы элементов управления
	hEdit1 = GetDlgItem(hDialog, IDC_EDIT1);
	hEdit2 = GetDlgItem(hDialog, IDC_EDIT2);
	hButton1 = GetDlgItem(hDialog, IDC_BUTTON1);
	hButton2 = GetDlgItem(hDialog, IDC_BUTTON2);
	hCheck1 = GetDlgItem(hDialog, IDC_CHECK1);
	hCheck2 = GetDlgItem(hDialog, IDC_CHECK2);

	// меню из ресурсов приложения
	hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

	// дескрипторы подменю
	hSubMenu = GetSubMenu(hMenu, 0);
	hSubMenu2 = GetSubMenu(hSubMenu, 0);
	hSubMenu3 = GetSubMenu(hSubMenu, 1);

	// установка отметки на первом пункте в радио-группе элементов меню 
	CheckMenuRadioItem(hSubMenu3, ID_GROUP2_BUTTON, ID_GROUP2_CHECKBOX, ID_GROUP2_CHECKBOX, MF_BYCOMMAND);
	
  paHbm = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
  SetMenuItemBitmaps(hMenu, ID_GROUP1_BUTTON, MF_BYCOMMAND, paHbm, paHbm);

  return TRUE;
}

// обработчик сообщения WM_COMMAND будет вызван при выборе пункта меню
void CContextMenuDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id >= ID_GROUP1_BUTTON && id <= ID_GROUP1_CHECKBOX)
	{
		switch(id)
		{
		case ID_GROUP1_BUTTON:
			if(dwButtonState == MF_CHECKED){
				EnableWindow(hButton1, FALSE);
				dwButtonState = MF_UNCHECKED;
			}
			else{
				EnableWindow(hButton1, TRUE);
				dwButtonState = MF_CHECKED;
			}
			CheckMenuItem(hSubMenu2, ID_GROUP1_BUTTON, MF_BYCOMMAND | dwButtonState);
			break;
		case ID_GROUP1_EDIT:
			if(dwEditState == MF_CHECKED){
				EnableWindow(hEdit1, FALSE);
				dwEditState=MF_UNCHECKED;
			}
			else{
				EnableWindow(hEdit1, TRUE);
				dwEditState=MF_CHECKED;
			}
			CheckMenuItem(hSubMenu2, ID_GROUP1_EDIT, MF_BYCOMMAND | dwEditState);
			break;
		case ID_GROUP1_CHECKBOX:
			if(dwCheckboxState == MF_CHECKED){
				EnableWindow(hCheck1, FALSE);
				dwCheckboxState = MF_UNCHECKED;
			}
			else{
				EnableWindow(hCheck1, TRUE);
				dwCheckboxState = MF_CHECKED;
			}
			CheckMenuItem(hSubMenu2, ID_GROUP1_CHECKBOX, MF_BYCOMMAND | dwCheckboxState);
			break;
		}
	}
	if(id >= ID_GROUP2_BUTTON && id <= ID_GROUP2_CHECKBOX)
	{
		// установка отметки на выбранном пункте в радио-группе элементов меню 
		CheckMenuRadioItem(hSubMenu3, ID_GROUP2_BUTTON, ID_GROUP2_CHECKBOX, id, MF_BYCOMMAND);
		switch(id)
		{
		case ID_GROUP2_BUTTON:
			EnableWindow(hButton2, TRUE);
			EnableWindow(hEdit2, FALSE);
			EnableWindow(hCheck2, FALSE);
			break;
		case ID_GROUP2_EDIT:
			EnableWindow(hButton2, FALSE);
			EnableWindow(hEdit2, TRUE);
			EnableWindow(hCheck2, FALSE);
			break;
		case ID_GROUP2_CHECKBOX:
			EnableWindow(hButton2, FALSE);
			EnableWindow(hEdit2, FALSE);
			EnableWindow(hCheck2, TRUE);
			break;
		}
	}
}

// обработчик сообщения WM_CONTEXTMENU будет вызван при щелчке правой кнопкой мыши в любой области диалогового окна
void CContextMenuDlg::Cls_OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)
{
	// отображение контекстное меню,
	// левый верхний угол которого привязывается к точке текущего положения курсора мыши
	TrackPopupMenu(hSubMenu, TPM_CENTERALIGN, xPos, yPos, 0, hDialog, 0);
}

void CContextMenuDlg::Cls_OnMyMeth(HWND hwnd, HWND hwnd2, UINT message, WPARAM wParam, LPARAM lParam)
{
	EndDialog(hwnd, 0);
}

BOOL CALLBACK CContextMenuDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CONTEXTMENU, ptr->Cls_OnContextMenu);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, ptr->Cls_OnMyMeth);
	}
	return FALSE;
}