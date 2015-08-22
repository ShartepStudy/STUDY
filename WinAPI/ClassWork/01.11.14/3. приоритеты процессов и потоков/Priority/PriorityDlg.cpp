#include "PriorityDlg.h"

CPriorityDlg* CPriorityDlg::ptr = NULL;

CPriorityDlg::CPriorityDlg(void)
{
	ptr = this;
}

void CPriorityDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

// https://ru.wikipedia.org/wiki/%D0%9C%D0%BD%D0%BE%D0%B3%D0%BE%D0%BF%D0%BE%D1%82%D0%BE%D1%87%D0%BD%D0%BE%D1%81%D1%82%D1%8C многопоточность

// http://wm-help.net/books-online/print-page/59464/59464-23.html рихтер!

BOOL CPriorityDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);

	// http://stackoverflow.com/questions/13631644/setthreadpriority-and-setpriorityclass 
	// http://msdn.microsoft.com/en-us/library/windows/desktop/ms686219(v=vs.85).aspx SetPriorityClass function

	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	return TRUE;
}

DWORD WINAPI Thread1(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

DWORD WINAPI Thread2(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

DWORD WINAPI Thread3(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

void CPriorityDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// http://uk.wikipedia.org/wiki/%D0%9E%D0%B1%27%D1%94%D0%BA%D1%82%D0%BD%D0%B8%D0%B9_%D0%9C%D0%B5%D0%BD%D0%B5%D0%B4%D0%B6%D0%B5%D1%80_(Windows) объектный менеджер windows
	// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724515(v=vs.85).aspx типы объектов windows

	if (id == IDC_REALTIME)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread1, hEdit1, 0, NULL);
		CloseHandle(hThread);
	}
	else if (id == IDC_NORMAL)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread2, hEdit2, 0, NULL);
		CloseHandle(hThread);
	}
	else if (id == IDC_IDLE)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread3, hEdit3, 0, NULL);
		CloseHandle(hThread);
	}
}

BOOL CALLBACK CPriorityDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}