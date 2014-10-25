#include "MainModalDialog.h"
#include "ModelessDlg.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hEdit1, TEXT("Напиши здесь что-то и нажми на кнопку!"));
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		// Проверим, открыто ли дополнительное немодальное окно
		if(CModelessDialog::hAddDialog) 
		{
			//Активизируем дополнительное немодальное окно
			SetForegroundWindow(CModelessDialog::hAddDialog);
			return;
		}
		CModelessDialog dlg;
		// Создаем немодальное диалоговое окно
		CModelessDialog::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CModelessDialog::DlgProc);
		// Отображаем окно	
		ShowWindow(CModelessDialog::hAddDialog, SW_RESTORE); 
		TCHAR buffer[200];
		// Получаем текст с текстового поля ввода
		GetWindowText(hEdit1, buffer, 200);
		// Отображаем текст на статике дополнительного диалога
	    SetWindowText(dlg.hStatic, buffer);
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
