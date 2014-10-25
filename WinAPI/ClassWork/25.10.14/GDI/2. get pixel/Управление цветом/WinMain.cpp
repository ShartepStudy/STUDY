#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HDC g_hDC = NULL;
HDC g_hMemoryDC = NULL;

HBITMAP g_hBitmap = NULL;
HPEN g_hPen = NULL;

RECT g_clientRectangle = {};
RECT g_colorRectangle = {};
RECT g_textRectangle = {};

COLORREF g_currentColor = 0;

TCHAR g_szText[200] = {};

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
	DeleteObject(g_hPen);

    // Освобождение совместимого контекста устройства в памяти.
	// http://efrazrabotka.ru/46/
	DeleteDC(g_hMemoryDC); 

	// Освобождение контекста устройства окна.
	ReleaseDC(hWindow, g_hDC); 

    EndDialog(hWindow, 0);
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam) 
{
	// Получение прямоугольника, охватывающего клиентскую область диалога.
	GetClientRect(hWindow, &g_clientRectangle);

	g_colorRectangle = g_clientRectangle;
	g_textRectangle = g_clientRectangle;

	g_colorRectangle.left = (g_clientRectangle.right - g_clientRectangle.left) / 2;
	g_textRectangle.right = (g_clientRectangle.right - g_clientRectangle.left) / 3;

    // Прозрачное перо.
	g_hPen = CreatePen(PS_NULL, 1, 0);

	// Получение контекста устройства для окна, в котором будет выводится изображение.
	g_hDC = GetDC(hWindow);

	// Получение совместимого контекста устройства памяти.
	g_hMemoryDC = CreateCompatibleDC(g_hDC);

	// Создание в памяти растрового изображения, совместимого с заданным контекстом устройства.
	g_hBitmap = CreateCompatibleBitmap(g_hDC, g_clientRectangle.right, g_clientRectangle.bottom);

	// Выбор растрового изображения в контекст устройства памяти.
	SelectObject(g_hMemoryDC, g_hBitmap);

	// Заполнение белым цветом растрового изображения, выбранного в контекст памяти.
	PatBlt(g_hMemoryDC, 0, 0, g_clientRectangle.right, g_clientRectangle.bottom, WHITENESS);

	// Выбор в контекст памяти стандартной системной кисти.
	SelectObject(g_hMemoryDC, GetStockObject(DC_BRUSH));

	// Выбор прозрачного пера в контекст устройства памяти.
	SelectObject(g_hMemoryDC, g_hPen);

	// Создание таймера.
	SetTimer(hWindow, 1, 50, NULL);

    return TRUE;
}

VOID OnPaint(HWND hWindow)
{
    PAINTSTRUCT paintStruct = {};

    // Получение контекста устройства, ассоциированного с основным окном.
    HDC hFormDC = BeginPaint(hWindow, &paintStruct);

    // Копирование изображения из контекста устройства памяти в контекст устройства окна.
    BitBlt(hFormDC, 0, 0, g_clientRectangle.right, g_clientRectangle.bottom, g_hMemoryDC, 0, 0, 
        SRCCOPY);

    // Освобождение контекста устройства.
    EndPaint(hWindow, &paintStruct);
}

VOID OnTimer(HWND hWindow, UINT uID)
{
    POINT point = {};
    static COLORREF previousColor = 0;

    // Получение позиции курсора в экранных координатах.
    GetCursorPos(&point);

    // Получение контекста устройства для всего экрана.
    HDC hDesktopDC = GetDC(NULL);

    // Получение цвета пикселя под курсором.
    g_currentColor = GetPixel(hDesktopDC, point.x, point.y);

    // Освобождение контекста устройства.
    ReleaseDC(NULL, hDesktopDC);

    // Проверка, отличается ли цвет текущего пикселя от цвета предыдущего.
    if (g_currentColor != previousColor)
    {
	    // Формирование строки для последующего вывода на экран.
	    _stprintf_s(g_szText, TEXT("\n  R: %d\n  G: %d\n  B: %d\n\n  #%.2X%.2X%.2X"), 
            GetRValue(g_currentColor), GetGValue(g_currentColor), GetBValue(g_currentColor), 
            GetRValue(g_currentColor), GetGValue(g_currentColor), GetBValue(g_currentColor));

	    // Заполнение белым цветом растрового изображения, выбранного в контекст памяти.
	    PatBlt(g_hMemoryDC, 0, 0, g_clientRectangle.right, g_clientRectangle.bottom, WHITENESS);

	    // Установка цвета кисти, выбранной в контекст устройства.
	    SetDCBrushColor(g_hMemoryDC, g_currentColor);

	    // Рисование прямоугольника, который будет заполнен цветом, соответствующим пикселю под 
        // курсором.
	    Rectangle(g_hMemoryDC, g_colorRectangle.left, g_colorRectangle.top, g_colorRectangle.right, 
            g_colorRectangle.bottom);

	    // Вывод текста, содержащего значения каждой составляющей для текущего цвета.
	    DrawText(g_hMemoryDC, g_szText, _tcslen(g_szText), &g_textRectangle, DT_CENTER);

	    // Отправка приложению сообщения WM_PAINT.
	    InvalidateRect(hWindow, NULL, TRUE);
    }

    // Запоминание текущего цвета.
    previousColor = g_currentColor;
}