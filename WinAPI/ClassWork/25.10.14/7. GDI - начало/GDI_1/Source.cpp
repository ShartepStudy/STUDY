#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HBITMAP g_hBitmap = NULL;

HBRUSH g_hBrush1 = NULL;
HBRUSH g_hBrush2 = NULL;

HPEN g_hPens[5] = {};

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID Draw(HDC hDC, INT nShift);
VOID OnClose(HWND hWindow);
VOID OnCommand(HWND hWindow, INT nID, HWND hControl, UINT uCodeNotify);
HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnPaint(HWND hWindow);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, INT nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProcedure); 
}

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
    switch (nMessage)
    {
        HANDLE_MSG(hWindow, WM_CLOSE, OnClose);
        HANDLE_MSG(hWindow, WM_COMMAND, OnCommand);
        HANDLE_MSG(hWindow, WM_CTLCOLORDLG, OnCtlColor);
        HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hWindow, WM_PAINT, OnPaint);
    }

    return FALSE;
}

VOID Draw(HDC hDC, INT nShift)
{
    POINT point = {};

    for (INT i = 0; i < ARRAYSIZE(g_hPens); i++)
    {
	    SelectObject(hDC, g_hPens[i]);
	    MoveToEx(hDC, 30, i * 30 + nShift, &point);
	    LineTo(hDC, 400, i * 30 + nShift);
    }

    Rectangle(hDC, 450, nShift, 550, nShift + 50);
    SelectObject(hDC, g_hPens[1]);
    Ellipse(hDC, 600, nShift, 700, nShift + 50);
    SelectObject(hDC, g_hPens[0]);
    SelectObject(hDC, g_hBrush1);
    Rectangle(hDC, 450, nShift + 70, 550, nShift + 120);
    Ellipse(hDC, 600, nShift + 70, 700, nShift + 120);
}

VOID OnClose(HWND hWindow)
{
    DeleteObject(g_hBrush1);
	DeleteObject(g_hBrush2);

	DeleteObject(g_hBitmap);

	for (INT i = 0; i < ARRAYSIZE(g_hPens); i++)
	{
		DeleteObject(g_hPens[i]);
	}

    EndDialog(hWindow, 0);
}

VOID OnCommand(HWND hWindow, INT nID, HWND hControl, UINT uCodeNotify)
{
    if (nID == IDOK)
    {
        HDC hDC = GetDC(hWindow);

        Draw(hDC, 280);

        ReleaseDC(hWindow, hDC);
    }
}

HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType)
{
    HBRUSH hBrush = NULL;

    if (nType == CTLCOLOR_DLG)
	{
		return  g_hBrush2;
	}

    return hBrush;
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam) 
{
    g_hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));

    g_hBrush1 = CreatePatternBrush(g_hBitmap);
    g_hBrush2 = CreateSolidBrush(RGB(255, 255, 255));

    g_hPens[0] = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
    g_hPens[1] = CreatePen(PS_DASH, 1, RGB(0, 255, 255));
    g_hPens[2] = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
    g_hPens[3] = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 255));
    g_hPens[4] = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 255));

    return TRUE;
}

VOID OnPaint(HWND hWindow)
{
    PAINTSTRUCT paintStruct = {};
    HDC hDC = BeginPaint(hWindow, &paintStruct);

    Draw(hDC, 50);

    EndPaint(hWindow, &paintStruct);
}