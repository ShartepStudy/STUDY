#include <windows.h>
#include <windowsX.h>
#include <commctrl.h>
#include <tchar.h>
#include "resource2.h"

#pragma comment(lib,"comctl32")

class CWaitableTimerDlg
{
public:
	CWaitableTimerDlg(void);
	~CWaitableTimerDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CWaitableTimerDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);

	// обработчик пользовательского сообщения
	void OnTrayIcon(WPARAM wp, LPARAM lp);
	HWND hButton, hEdit1, hSpin1, hEdit2, hSpin2, hEdit3, hSpin3, hDialog;
	HICON hIcon;
	PNOTIFYICONDATA pNID;
};
// WaitableTimerDlg.cpp
#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER

CWaitableTimerDlg* CWaitableTimerDlg::ptr = NULL;

CWaitableTimerDlg::CWaitableTimerDlg(void)
{
	ptr = this;
	pNID = new NOTIFYICONDATA;
}

CWaitableTimerDlg::~CWaitableTimerDlg(void)
{
	delete pNID;
}

void CWaitableTimerDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CWaitableTimerDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	// Получим дескрипторы элементов управления

	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);

	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);

	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);

	hButton = GetDlgItem(hwnd, IDC_BUTTON1);
	hDialog = hwnd;

	// Получим дескриптор экземпляра приложения
	HINSTANCE hInst = GetModuleHandle(NULL);
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // загружаем иконку
	// устанавливаем иконку в главном окне приложения
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon)); 
	memset(pNID, 0, sizeof(NOTIFYICONDATA)); //Обнуление структуры
	pNID->cbSize = sizeof(NOTIFYICONDATA); //размер структуры
	// иконка, которая будет отображаться в области уведомлений
	pNID->hIcon = hIcon;

	// дескриптор окна, которое будет получать уведомляющие сообщения,
	// ассоциированные с иконкой в области уведомлений
	pNID->hWnd = hwnd;
	lstrcpy(pNID->szTip, TEXT("Будильник")); // Подсказка
	pNID->uCallbackMessage = WM_ICON; // Пользовательское сообщение
	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	// NIF_ICON - поле hIcon содержит корректное значение (позволяет создать иконку в области уведомления).
	// NIF_MESSAGE - поле uCallbackMessage содержит корректное значение
	// (позволяет получать сообщения от иконки в трэе).
	// NIF_TIP - поле szTip содержит корректное значение (позволяет создать всплывающую подсказку для иконки в области уведомления).
	// NIF_INFO - поле szInfo содержит корректное значение (позволяет создать Balloon подсказку для иконки в области уведомления).
	lstrcpy(pNID->szInfo, TEXT("Приложение демонстрирует работу таймера синхронизации"));
	lstrcpy(pNID->szInfoTitle, TEXT("Будильник!"));
	pNID->uID = ID_TRAYICON; // предопределённый идентификатор иконки
	return TRUE;
}

DWORD WINAPI Thread(LPVOID lp)
{

	CWaitableTimerDlg* p = (CWaitableTimerDlg*)lp;
	// создаем таймер синхронизации
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	TCHAR buf[10];
	int hours, minutes, seconds;
	GetWindowText(p->hEdit1, buf, 10);
	hours = _tstoi(buf);
	GetWindowText(p->hEdit2, buf, 10);
	minutes = _tstoi(buf);
	GetWindowText(p->hEdit3, buf, 10);
	seconds = _tstoi(buf);
	SYSTEMTIME st;
	GetLocalTime(&st); // получим текущее локальное время
	if(st.wHour > hours || st.wHour == hours && st.wMinute > minutes || 
		st.wHour == hours && st.wMinute == minutes && st.wSecond > seconds)
	{
		CloseHandle(hTimer);
		EnableWindow(p->hButton, TRUE);
		EnableWindow(p->hEdit1, TRUE);
		EnableWindow(p->hEdit2, TRUE);
		EnableWindow(p->hEdit3, TRUE);
		return 0;
	}
	st.wHour = hours;
	st.wMinute = minutes;
	st.wSecond = seconds;
	FILETIME ft;
	// преобразуем структуру SYSTEMTIME в FILETIME
	SystemTimeToFileTime(&st, &ft); 
	// преобразуем местное время в UTC-время
	LocalFileTimeToFileTime(&ft, &ft); 
	// устанавливаем таймер синхронизации
	SetWaitableTimer(hTimer, (LARGE_INTEGER *)&ft, 0, NULL, NULL, FALSE); 


	// ожидаем переход таймера в сигнальное состояние
	if(WaitForSingleObject(hTimer, INFINITE) == WAIT_OBJECT_0)
	{
		Shell_NotifyIcon(NIM_DELETE, p->pNID); // Удаляем иконку из трэя
		ShowWindow(p->hDialog, SW_NORMAL); // Восстанавливаем окно
		// устанавливаем окно на передний план
		SetForegroundWindow(p->hDialog); 
		for(int i = 0; i < 5; i++)
		{
			Beep(1000, 500);
			Sleep(500);
		}
	}
	CancelWaitableTimer(hTimer); // отменяем таймер
	CloseHandle(hTimer); // закрываем дескриптор таймера
	EnableWindow(p->hButton, TRUE);
	EnableWindow(p->hEdit1, TRUE);
	EnableWindow(p->hEdit2, TRUE);
	EnableWindow(p->hEdit3, TRUE);
	return 0;
}

void CWaitableTimerDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		HANDLE h;
		h = CreateThread(NULL, 0, Thread, this, 0, NULL);
		CloseHandle(h);
		EnableWindow(hButton, FALSE);
		EnableWindow(hEdit1, FALSE);
		EnableWindow(hEdit2, FALSE);
		EnableWindow(hEdit3, FALSE);
		ShowWindow(hwnd, SW_HIDE); // Прячем окно
		Shell_NotifyIcon(NIM_ADD, pNID); // Добавляем иконку в трэй
	}
}

void CWaitableTimerDlg::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if(state == SIZE_MINIMIZED)
	{
		ShowWindow(hwnd, SW_HIDE); // Прячем окно
		Shell_NotifyIcon(NIM_ADD, pNID); // Добавляем иконку в трэй
	}
}

// обработчик пользовательского сообщения
void CWaitableTimerDlg::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	// WPARAM - идентификатор иконки
	// LPARAM - сообщение от мыши или клавиатурное сообщение
	if(lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // Удаляем иконку из трэя

		ShowWindow(hDialog, SW_NORMAL); // Восстанавливаем окно
		// устанавливаем окно на передний план
		SetForegroundWindow(hDialog);	
	}
}

BOOL CALLBACK CWaitableTimerDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}
	// пользовательское сообщение
	if(message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	CWaitableTimerDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, CWaitableTimerDlg::DlgProc);
}
