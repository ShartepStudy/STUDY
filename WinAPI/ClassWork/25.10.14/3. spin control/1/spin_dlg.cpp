#include "spin_dlg.h"

CSpinControlDlg* CSpinControlDlg::ptr = NULL;

CSpinControlDlg::CSpinControlDlg(void)
{
	ptr = this;
}

void CSpinControlDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CSpinControlDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	hSpin = GetDlgItem(hDialog, IDC_SPIN1);
	hEdit1 = GetDlgItem(hDialog, IDC_EDIT1);
	hEdit2 = GetDlgItem(hDialog, IDC_EDIT2);

	// диапазон счетчика
	SendMessage(hSpin, UDM_SETRANGE32, 1, 10000);

	// правило приращения (с третьей секунды будет по +100)
	UDACCEL pAcceleration[3] = {{1,10}, {3,100}, {5,500}};
	SendMessage(hSpin, UDM_SETACCEL, 3, LPARAM(pAcceleration));

	// установка "приятеля"
	SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit2), 0);

	SetWindowText(hEdit2, TEXT("100"));
	SetWindowText(hEdit1, TEXT("Общий элемент управления Spin Control"));
	return TRUE;
}

void CSpinControlDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON2)
	{
		// текущая позиция счетчика
		int nTime = SendMessage(hSpin, UDM_GETPOS32, 0, 0);
		SetTimer(hwnd, 1, nTime, NULL);
		// текст из Edit Control
		GetWindowText(hEdit1, text, 300);
		count = 1;
	}
}

void CSpinControlDlg::Cls_OnTimer(HWND hwnd, UINT id)
{
	TCHAR copytext[300] = {0};
	if (count <= _tcslen(text)) // вывели весь текст?
	{
		// если нет, добавить к заголовку один символ
		_tcsncpy(copytext, text, count++);
		// вывести текст в заголовок главного окна
		SetWindowText(hwnd, copytext);
	}
	else 
	{
		// если да, удалить таймер
		KillTimer(hwnd, 1);
	}
}

BOOL CALLBACK CSpinControlDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, ptr->Cls_OnTimer);
	}
	return FALSE;
}