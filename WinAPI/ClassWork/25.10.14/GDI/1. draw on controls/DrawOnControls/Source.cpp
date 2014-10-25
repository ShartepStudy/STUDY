#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND g_hEdit1 = NULL;
HWND g_hEdit2 = NULL;
HWND g_hListBox = NULL;
HWND g_hStatic = NULL;

HBITMAP g_hBitmap = NULL;

HBRUSH g_hBrush1 = NULL;
HBRUSH g_hBrush2 = NULL;
HBRUSH g_hBrush3 = NULL;
HBRUSH g_hBrush4 = NULL;

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnTimer(HWND hWindow, UINT uID);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, INT nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure);
}

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	switch (nMessage)
	{
		HANDLE_MSG(hWindow, WM_CLOSE, OnClose);
		HANDLE_MSG(hWindow, WM_CTLCOLOREDIT, OnCtlColor);
		HANDLE_MSG(hWindow, WM_CTLCOLORBTN, OnCtlColor);
		HANDLE_MSG(hWindow, WM_CTLCOLORDLG, OnCtlColor);
		HANDLE_MSG(hWindow, WM_CTLCOLORLISTBOX, OnCtlColor);
		HANDLE_MSG(hWindow, WM_CTLCOLORSTATIC, OnCtlColor);
		HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
		HANDLE_MSG(hWindow, WM_TIMER, OnTimer);
	}

	return FALSE;
}

VOID OnClose(HWND hWindow)
{
	DeleteObject(g_hBrush1);
	DeleteObject(g_hBrush2);
	DeleteObject(g_hBrush3);
	DeleteObject(g_hBrush4);

	DeleteObject(g_hBitmap);

	EndDialog(hWindow, 0);
}

HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType)
{
	HBRUSH hBrush = NULL;

	switch (nType)
	{
	case CTLCOLOR_EDIT:
	{
						  if (GetDlgCtrlID(hChild) == IDC_EDIT1)
						  {
							  SetTextColor(hDC, RGB(255, 255, 0));
							  SetBkMode(hDC, TRANSPARENT);
							  hBrush = g_hBrush2;
							  break;
						  }
						  else if (GetDlgCtrlID(hChild) == IDC_EDIT2)
						  {
							  SetTextColor(hDC, RGB(255, 0, 0));
							  SetBkMode(hDC, OPAQUE);
							  hBrush = g_hBrush3;
							  break;
						  }
	}
	case CTLCOLOR_DLG:
		hBrush = g_hBrush1;
		break;
	case CTLCOLOR_BTN:
		hBrush = g_hBrush3;
		break;
	case CTLCOLOR_LISTBOX:
		SetBkMode(hDC, TRANSPARENT);
		hBrush = g_hBrush4;
		break;
	case CTLCOLOR_STATIC:
		hBrush = g_hBrush1;
		break;
	}

	return hBrush;
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam)
{
	g_hEdit1 = GetDlgItem(hWindow, IDC_EDIT1);
	g_hEdit2 = GetDlgItem(hWindow, IDC_EDIT2);
	g_hListBox = GetDlgItem(hWindow, IDC_LIST);
	g_hStatic = GetDlgItem(hWindow, IDC_STATIC1);

	g_hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));

	g_hBrush1 = CreatePatternBrush(g_hBitmap);
	g_hBrush2 = CreateSolidBrush(RGB(0, 0, 255));
	g_hBrush3 = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0));
	g_hBrush4 = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));

	SendMessage(g_hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Graphics device interface"));
	SetWindowText(g_hEdit1, TEXT("Graphics\r\ndevice\r\ninterface"));
	SetWindowText(g_hEdit2, TEXT("Graphics\r\ndevice\r\ninterface"));

	SetTimer(hWindow, 1, 1000, NULL);

	return TRUE;
}

VOID OnTimer(HWND hWindow, UINT uID)
{
	HDC hDC1 = GetDC(hWindow);
	HDC hDC2 = GetDC(g_hStatic);

	TCHAR szText[] = TEXT("Graphics device interface");

	SetBkMode(hDC1, TRANSPARENT);
	SetTextColor(hDC1, RGB(255, 0, 0));
	SetBkColor(hDC2, RGB(255, 0, 255));
	SetTextColor(hDC2, RGB(0, 255, 0));

	static BOOL fFlag = true;

	if (fFlag)
	{
		TextOut(hDC1, 400, 300, szText, _tcslen(szText));
		TextOut(hDC2, 60, 40, szText, _tcslen(szText));
	}
	else
	{
		InvalidateRect(g_hStatic, NULL, TRUE);
		InvalidateRect(hWindow, NULL, TRUE);
	}

	fFlag = !fFlag;

	ReleaseDC(hWindow, hDC1);
	ReleaseDC(g_hStatic, hDC2);
}