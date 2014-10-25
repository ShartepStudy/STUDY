#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HDC g_hDC = NULL;
HDC g_hMemoryDC = NULL;

HBRUSH g_hBrush1 = NULL;
HBRUSH g_hBrush2 = NULL;

HBITMAP g_hBitmap1 = NULL;
HBITMAP g_hBitmap2 = NULL;

HPEN g_hPen = NULL;

UINT g_uHeight = 0;
UINT g_uWidth = 0;

INT g_nX = 0;
INT g_nY = 0;

INT g_nDX = 2;
INT g_nDY = 5;

INT g_nSize = 50;

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnPaint(HWND hWindow);
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
        HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hWindow, WM_PAINT, OnPaint);
        HANDLE_MSG(hWindow, WM_TIMER, OnTimer);
    }

    return FALSE;
}

VOID OnClose(HWND hWindow)
{
    // Освобождение ресурсов.
	DeleteObject(g_hBrush1);
	DeleteObject(g_hBrush2);
	DeleteObject(g_hBitmap1);
	DeleteObject(g_hBitmap2);
	DeleteObject(g_hPen);

    // Освобождение совместимого контекста устройства в памяти.
	DeleteDC(g_hMemoryDC);

	// Освобождение контекста устройства окна.
	ReleaseDC(hWindow, g_hDC);

    EndDialog(hWindow, 0);
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam) 
{
    // Загрузка изображения из ресурсов приложения.
    g_hBitmap1 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
    g_hBitmap2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));

    // Создание кисти с растровым наполнением.
    g_hBrush1 = CreatePatternBrush(g_hBitmap1);
    g_hBrush2 = CreatePatternBrush(g_hBitmap2);

    // Создание прозрачного пера.
    g_hPen = CreatePen(PS_NULL, 1, 0);

    // Получение контекста устройства для окна, в котором будет выводится изображение.
    g_hDC = GetDC(hWindow);

    // Получение совместимого контекста устройства памяти.
    g_hMemoryDC = CreateCompatibleDC(g_hDC);

    // Выбор растрового изображения в контексте устройства памяти.
    SelectObject(g_hMemoryDC, g_hBitmap1);

    // Выбор прозрачного пера в контексте устройства памяти.
    SelectObject(g_hMemoryDC, g_hPen);

    // Выбор кисти в контексте устройства памяти.
    SelectObject(g_hMemoryDC, g_hBrush2);

    // Создание таймера.
    SetTimer(hWindow, 1, 15, NULL);

    return TRUE;
}

VOID OnPaint(HWND hWindow)
{
    PAINTSTRUCT paintStruct = {};

    // Получение контекста устройства, ассоциированного с основным окном.
    HDC hDC = BeginPaint(hWindow, &paintStruct);

    // Копирование изображения из контекста устройства памяти в контекст устройства окна.
    BitBlt(hDC, 0, 0, g_uWidth, g_uHeight, g_hMemoryDC, 0, 0, SRCCOPY);

    // Освобождение контекста устройства.
    EndPaint(hWindow, &paintStruct);
}

VOID OnTimer(HWND hWindow, UINT uID)
{
    RECT clientRectangle = {};

    // Получение прямоугольника, охватывающего клиентскую область диалога.
    GetClientRect(hWindow, &clientRectangle);

    g_uHeight = clientRectangle.bottom;
    g_uWidth = clientRectangle.right;

    SelectObject(g_hMemoryDC, g_hBrush1);

    // Восстановление фонового изображения.
    Ellipse(g_hMemoryDC, g_nX, g_nY, g_nX + g_nSize, g_nY + g_nSize);

    g_nX += g_nDX;
    g_nY += g_nDY;

    if (g_nX + g_nSize >= clientRectangle.right || g_nX <= 0)
    {
	    g_nDX = -g_nDX;
    }
    if (g_nY <=0 || g_nY + g_nSize >= clientRectangle.bottom)
    {
	    g_nDY = -g_nDY;
    }

    SelectObject(g_hMemoryDC, g_hBrush2);

    // Рисование эллипса на новом месте.
    Ellipse(g_hMemoryDC, g_nX, g_nY, g_nX + g_nSize, g_nY + g_nSize);

    // Вызов обработчика сообщения WM_PAINT.
    InvalidateRect(hWindow, NULL, FALSE);
}