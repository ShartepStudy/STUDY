#include "OnlyOneCopyDlg.h"

OnlyOneCopyDlg* OnlyOneCopyDlg::ptr = NULL;

OnlyOneCopyDlg::OnlyOneCopyDlg(void)
{
	ptr = this;
}

void OnlyOneCopyDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL OnlyOneCopyDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	TCHAR GUID[] = TEXT("{D99CD3E0-670D-4def-9B74-99FD7E793DFB}");
	hMutex = CreateMutex(0, FALSE, GUID);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_OBJECT_0) // Контролируемый объект ядра перешел в свободное (сигнальное) состояние, т.е. произошел захват мьютекса
	{
		SetWindowText(hwnd, L"Первая копия!");
	}
	else if (dwAnswer == WAIT_TIMEOUT) // Истек  интервал  тайм-аута, а  контролируемый объект ядра остался в занятом (несигнальном) состоянии
	{
		MessageBox(hwnd, TEXT("Нельзя запустить более одной копии приложения!"), TEXT("Мьютекс"), MB_OK | MB_ICONSTOP);
		EndDialog(hwnd, 0);
	}
	return TRUE;
}

void OnlyOneCopyDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK || id == IDCANCEL)
		EndDialog(hwnd, 0);
}

BOOL CALLBACK OnlyOneCopyDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}