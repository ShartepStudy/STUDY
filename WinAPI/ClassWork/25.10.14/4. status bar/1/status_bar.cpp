#include "status_bar_dlg.h"

CStatusBarDlg* CStatusBarDlg::ptr = NULL;

CStatusBarDlg::CStatusBarDlg(void)
{
	ptr = this;
}

void CStatusBarDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CStatusBarDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;

	// дескрипторы элементов управления
	hSpin = GetDlgItem(hDialog, IDC_SPIN1);
	hEdit = GetDlgItem(hDialog, IDC_EDIT2);
	hCheck1 = GetDlgItem(hDialog, IDC_CHECK1);
	hCheck2 = GetDlgItem(hDialog, IDC_CHECK2);

	// диапазон счётчика
	SendMessage(hSpin, UDM_SETRANGE32, 0, 100);
	// установка "приятеля" для счётчика
	SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit), 0);
	SetWindowText(hEdit, TEXT("0"));

	// создание строки состояния
	hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_TOOLTIPS | SBARS_SIZEGRIP, 0, hDialog, WM_USER);

	// разделение строки состояния на отдельные секции
	int parts[4] = {40, 120, 240, -1};
	SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)parts);

	// для каждой секции можно установить текст и всплывающую подсказку
	SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM) TEXT("Счётчик: 0"));
	SendMessage(hStatus, SB_SETTIPTEXT, 1, (LPARAM) TEXT("Счётчик: 0"));
	SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM) TEXT("Флажок 1: ОТКЛ"));
	SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM) TEXT("Флажок 1: ОТКЛ"));
	SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM) TEXT("Флажок 2: ОТКЛ"));
	SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM) TEXT("Флажок 2: ОТКЛ"));

	// загрузка иконки из ресурсов
	hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));

	// установка иконки в первую секцию строки состояния
	SendMessage(hStatus, SB_SETICON, 0, (LPARAM) hIcon);

	// установка цвета фона строки состояния
	SendMessage(hStatus, SB_SETBKCOLOR, 0, (LPARAM) RGB(255, 200, 255));

	return TRUE;
}

void CStatusBarDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// статус флажков в строке состояния
	if(id == IDC_CHECK1)
	{
		LRESULT lResult = SendMessage(hCheck1, BM_GETCHECK, 0, 0);
		if(lResult == BST_CHECKED)
		{
			SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM) TEXT("Флажок 1: ВКЛ"));
			SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM) TEXT("Флажок 1: ВКЛ"));
		}
		else
		{
			SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM) TEXT("Флажок 1: ОТКЛ"));
			SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM) TEXT("Флажок 1: ОТКЛ"));
		}
	}
	if(id == IDC_CHECK2)
	{
		LRESULT lResult = SendMessage(hCheck2, BM_GETCHECK, 0, 0);
		if(lResult == BST_CHECKED)
		{
			SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM) TEXT("Флажок 2: ВКЛ"));
			SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM) TEXT("Флажок 2: ВКЛ"));
		}
		else
		{
			SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM) TEXT("Флажок 2: ОТКЛ"));
			SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM) TEXT("Флажок 2: ОТКЛ"));
		}
	}
}

void CStatusBarDlg::Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	// обработчик сообщения нажатия на одну из стрелок счётчика
	TCHAR buf[30];
	wsprintf(buf, TEXT("Счётчик: %d"), pos);
	// состояние счётчика в строке состояния
	SendMessage(hStatus, SB_SETTEXT, 1,(LPARAM)buf);
	SendMessage(hStatus, SB_SETTIPTEXT, 1,(LPARAM)buf);
}

void CStatusBarDlg::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	// размер строки состояния, равный ширине клиентской области главного окна
	SendMessage(hStatus, WM_SIZE, 0, 0);
}

BOOL CALLBACK CStatusBarDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_VSCROLL, ptr->Cls_OnVScroll);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}
	return FALSE;
}