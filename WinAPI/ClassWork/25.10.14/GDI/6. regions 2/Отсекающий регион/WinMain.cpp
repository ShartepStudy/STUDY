#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HDC g_hForm = NULL;
HDC g_hMemDC = NULL;
HDC g_hFigureDC = NULL;

HBITMAP g_hBitmap = NULL;
HBITMAP g_hFigure1 = NULL;
HBITMAP g_hFigure2 = NULL;
HBITMAP g_hFigure3 = NULL;

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnLButtonDown(HWND hWindow, BOOL fDoubleClick, INT nX, INT nY, UINT uKeyFlags);
VOID OnPaint(HWND hWindow);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, INT nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure); 
}

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
    switch (nMessage)
    {
        HANDLE_MSG(hWindow, WM_CLOSE, OnClose);
        HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hWindow, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hWindow, WM_PAINT, OnPaint);
    }

    return FALSE;
}

VOID OnClose(HWND hWindow)
{
    DeleteObject(g_hFigure1);
	DeleteObject(g_hFigure2);
	DeleteObject(g_hFigure3);
	DeleteObject(g_hBitmap);

    ReleaseDC(hWindow, g_hForm);

	DeleteDC(g_hMemDC);
	DeleteDC(g_hFigureDC);

    EndDialog(hWindow, 0);
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam)
{
    g_hFigure1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	g_hFigure2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	g_hFigure3 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));

	MoveWindow(hWindow, 200, 200, 60, 80, TRUE);

	// Инициализация контекстов устройств.
	g_hForm = GetDC(hWindow);

	g_hMemDC = CreateCompatibleDC(g_hForm);
	g_hBitmap = CreateCompatibleBitmap(g_hForm, 60, 80);

	SelectObject(g_hMemDC, g_hBitmap);

	g_hFigureDC = CreateCompatibleDC(g_hForm);

	// Копирование в память первой картинки.
	SelectObject(g_hFigureDC, g_hFigure3);

	HRGN hRegion1 = CreateRectRgn(20, 20, 60, 40);
	HRGN hRegion2 = CreateRectRgn(0, 40, 40, 60);

	CombineRgn(hRegion1, hRegion1, hRegion2, RGN_OR);

	SelectClipRgn(g_hMemDC, hRegion1);

	DeleteObject(hRegion1);
	DeleteObject(hRegion2);

	BitBlt(g_hMemDC, 0, 20, 60, 40, g_hFigureDC, 0, 0, SRCCOPY);

	SelectClipRgn(g_hMemDC, NULL);

	// Копирование в память второй картинки.
	SelectObject(g_hFigureDC, g_hFigure1);

	hRegion1 = CreateRectRgn(0, 0, 60, 20);
	hRegion2 = CreateRectRgn(0, 20, 20, 40);

	CombineRgn(hRegion1, hRegion1, hRegion2, RGN_OR);

	SelectClipRgn(g_hMemDC, hRegion1);

	DeleteObject(hRegion1);
	DeleteObject(hRegion2);

	BitBlt(g_hMemDC, 0, 0, 60, 40, g_hFigureDC, 0, 0, SRCCOPY);

	SelectClipRgn(g_hMemDC, NULL);

	// Копирование в память третьей картинки.
	SelectObject(g_hFigureDC, g_hFigure2);

	hRegion1 = CreateRectRgn(40, 40, 60, 60);
	hRegion2 = CreateRectRgn(0, 60, 60, 80);

	CombineRgn(hRegion1, hRegion1, hRegion2, RGN_OR);

	SelectClipRgn(g_hMemDC, hRegion1);

	DeleteObject(hRegion1);
	DeleteObject(hRegion2);

	BitBlt(g_hMemDC, 0, 40, 60, 40, g_hFigureDC, 0, 0, SRCCOPY);

	SelectClipRgn(g_hMemDC, NULL);

    return TRUE;
}

VOID OnLButtonDown(HWND hWindow, BOOL fDoubleClick, INT nX, INT nY, UINT uKeyFlags)
{
	SendMessage(hWindow, WM_NCLBUTTONDOWN, HTCAPTION, 0);
}

VOID OnPaint(HWND hWindow)
{
    PAINTSTRUCT paintStruct = {};

    HDC hDC = BeginPaint(hWindow, &paintStruct);

    BitBlt(g_hForm, 0, 0, 60, 80, g_hMemDC, 0, 0, SRCCOPY);

    EndPaint(hWindow, &paintStruct);
}