#define _USE_MATH_DEFINES

#include <cmath>
#include <ctime>
#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(lib, "msimg32")

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HDC g_hBackgroundDC = NULL;
HDC g_hFormDC = NULL;
HDC g_hMemoryDC = NULL;

HBITMAP g_hBackgroundBitmap = NULL;
HBITMAP g_hMemoryBitmap = NULL;

INT g_nHeight = 0;
INT g_nWidth = 0;

FLOAT g_fltAngle = 0.0f;

XFORM g_xForm = {};

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
UINT OnGetDlgCode(HWND hWindow, LPMSG pMessage);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnPaint(HWND hWindow);
VOID OnTimer(HWND hWindow, UINT uID);
VOID Quit(HWND hWindow, INT nMessage, INT nX, INT nY);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, INT nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure); 
}

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
    switch (nMessage)
    {
        HANDLE_MSG(hWindow, WM_CLOSE, OnClose);
        HANDLE_MSG(hWindow, WM_GETDLGCODE, OnGetDlgCode);
        HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hWindow, WM_PAINT, OnPaint);
        HANDLE_MSG(hWindow, WM_TIMER, OnTimer);
    }

    // Если произойдет клавиатурное событие или событие мыши, то приложение должно завершиться.
    if (nMessage == WM_KEYDOWN || nMessage == WM_SYSKEYDOWN || nMessage >= WM_MOUSEFIRST && 
        nMessage <= WM_MOUSELAST)
    {
        Quit(hWindow, nMessage, LOWORD(lParam), HIWORD(lParam));
    }

    return FALSE;
}

VOID OnClose(HWND hWindow)
{
    ReleaseDC(hWindow, g_hFormDC);

	DeleteDC(g_hMemoryDC);
	DeleteDC(g_hBackgroundDC);

	DeleteObject(g_hMemoryBitmap);
	DeleteObject(g_hBackgroundBitmap);

    EndDialog(hWindow, 0);
}

UINT OnGetDlgCode(HWND hWindow, LPMSG pMessage)
{
    // Клавиатурные аппаратные сообщения будет получать диалоговая процедура.
    SetWindowLong(hWindow,	DWL_MSGRESULT, DLGC_WANTALLKEYS);

    return DLGC_WANTARROWS;
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam) 
{
    // Получение размеров экрана.
    g_nWidth = GetSystemMetrics(SM_CXSCREEN);
    g_nHeight = GetSystemMetrics(SM_CYSCREEN);
	
    // Получение контекста устройства окна.
    g_hFormDC = GetDC(hWindow);

    // Получение контекста рабочего стола.
    HDC hDesktopDC = GetDC(NULL); 
	
    // Получение контекста памяти для рисования часов.
    g_hMemoryDC = CreateCompatibleDC(hDesktopDC);
    g_hMemoryBitmap = CreateCompatibleBitmap(hDesktopDC, g_nWidth, g_nHeight);
    SelectObject(g_hMemoryDC, g_hMemoryBitmap);

    // Получение контекста памяти для фона.
    g_hBackgroundDC = CreateCompatibleDC(hDesktopDC);
    g_hBackgroundBitmap = CreateCompatibleBitmap(hDesktopDC, g_nWidth, g_nHeight);
    SelectObject(g_hBackgroundDC, g_hBackgroundBitmap);
	
    // Растягивание формы по размеру экрана.
    MoveWindow(hWindow, 0, 0, g_nWidth, g_nHeight, TRUE); 

    // Структура для полупрозрачности.
    BLENDFUNCTION blend = {}; 
    blend.BlendOp = AC_SRC_OVER;
    
    // Коэффициент полупрозрачности.
    blend.SourceConstantAlpha = 128;
    blend.AlphaFormat = AC_SRC_ALPHA;

    // Создание полупрозрачного фонового изображения.
    AlphaBlend(g_hBackgroundDC, 0, 0, g_nWidth, g_nHeight, hDesktopDC, 0, 0, g_nWidth, g_nHeight, 
        blend); 
    ReleaseDC(NULL, hDesktopDC); 
	
    // Перенаправление оси координат.
    SetMapMode(g_hMemoryDC, MM_ANISOTROPIC);

    // Переключение контекста устройства в графический режим, для использования мировой системы 
    // координат переключаем.
    SetGraphicsMode(g_hMemoryDC, GM_ADVANCED);

    // Установка прозрачного фона для букв.
    SetBkMode(g_hMemoryDC, TRANSPARENT);

    // Установка цвета текста.
    SetTextColor(g_hMemoryDC, 0x00FFFF);
    
    // Скрытие курсора.
    ShowCursor(FALSE);

    SetTimer(hWindow, 1, 1000, NULL);

    return TRUE;
}

VOID OnPaint(HWND hWindow)
{
    // Копирование фонового изображения в контекст памяти.
    BitBlt(g_hMemoryDC, 0, 0, g_nWidth, g_nHeight, g_hBackgroundDC, 0, 0, SRCCOPY);

    // Смещение начала координат в центр.
    SetViewportOrgEx(g_hMemoryDC, g_nWidth / 2, g_nHeight / 2, NULL); 

    // Установка направления осей координат: ось X вправо, ось Y вверх.
    SetViewportExtEx(g_hMemoryDC, 1, -1, NULL);
	
    // Рисование часов.

    // Рисование ободка.
    SelectObject(g_hMemoryDC, GetStockObject(NULL_BRUSH));
    HPEN pen = CreatePen(PS_SOLID, 3, 0x008CFF);
    HPEN pen2 = CreatePen(PS_SOLID, 6, 0x008CFF);
    SelectObject(g_hMemoryDC, pen);
    Ellipse(g_hMemoryDC, -330, -330, 330, 330);

    // Рисование разметки.
    INT nNumber = 0; 
    TCHAR szNumber[3] = {};

    for (g_fltAngle = 0; g_fltAngle < M_PI * 2; g_fltAngle += (FLOAT)(M_PI / 30), nNumber++)
    {
        g_xForm.eM11 = cos(g_fltAngle);
        g_xForm.eM12 = -sin(g_fltAngle);
        g_xForm.eM21 = sin(g_fltAngle);
        g_xForm.eM22 = cos(g_fltAngle);
        g_xForm.eDx = 0;
        g_xForm.eDy = 0;

        SetWorldTransform(g_hMemoryDC, &g_xForm);
        MoveToEx(g_hMemoryDC, 0, nNumber % 5 == 0 ? 300 : 310, NULL);
        LineTo(g_hMemoryDC, 0, 315);

        // Вывод цифр.
        if (nNumber % 5 == 0)
        {
            SetGraphicsMode(g_hMemoryDC, GM_COMPATIBLE);
            _stprintf_s(szNumber, TEXT("%d"), nNumber > 0 ? nNumber / 5 : 12);

            SIZE size = {};
            GetTextExtentPoint32(g_hMemoryDC, szNumber, _tcslen(szNumber), &size);

            TextOut(g_hMemoryDC, -size.cx / 2, 280-size.cy / 2, szNumber, _tcslen(szNumber));

            SetGraphicsMode(g_hMemoryDC, GM_ADVANCED);
        } 
    }

    // Рисование стрелок часов.

    // Рисование секундной стрелки.
    time_t currentTime = time(NULL); 
    tm dateAndTime = {};

    localtime_s(&dateAndTime, &currentTime); 

    g_fltAngle = (FLOAT)(dateAndTime.tm_sec * M_PI / 30);

    g_xForm.eM11 = cos(g_fltAngle);
    g_xForm.eM12 = -sin(g_fltAngle);
    g_xForm.eM21 = sin(g_fltAngle);
    g_xForm.eM22 = cos(g_fltAngle);

    SetWorldTransform(g_hMemoryDC, &g_xForm);
    MoveToEx(g_hMemoryDC, 0, 0, NULL);
    LineTo(g_hMemoryDC, 0, 250);
	
    // Рисование минутной стрелки.
    currentTime = time(NULL); 
    localtime_s(&dateAndTime, &currentTime); 

    g_fltAngle = (FLOAT)(dateAndTime.tm_min * M_PI / 30 + dateAndTime.tm_sec * M_PI / 1800);

    g_xForm.eM11 = cos(g_fltAngle);
    g_xForm.eM12 = -sin(g_fltAngle);
    g_xForm.eM21 = sin(g_fltAngle);
    g_xForm.eM22 = cos(g_fltAngle);

    SetWorldTransform(g_hMemoryDC, &g_xForm);
    MoveToEx(g_hMemoryDC, 0, 0, NULL);
    LineTo(g_hMemoryDC, 0, 200);

    // Рисование часовой стрелки.
    SelectObject(g_hMemoryDC, pen2);

    currentTime = time(NULL); 
    localtime_s(&dateAndTime, &currentTime); 

    g_fltAngle = (FLOAT)(dateAndTime.tm_hour * M_PI / 6 + dateAndTime.tm_min * M_PI / 360);

    g_xForm.eM11 = cos(g_fltAngle);
    g_xForm.eM12 = -sin(g_fltAngle);
    g_xForm.eM21 = sin(g_fltAngle);
    g_xForm.eM22 = cos(g_fltAngle);

    SetWorldTransform(g_hMemoryDC, &g_xForm);
    MoveToEx(g_hMemoryDC, 0, 0, NULL);
    LineTo(g_hMemoryDC, 0, 150);
    SelectObject(g_hMemoryDC, pen);
    ModifyWorldTransform(g_hMemoryDC, &g_xForm, MWT_IDENTITY);
	
    // Смещение началя координат в левый верхний угол.
    SetViewportOrgEx(g_hMemoryDC, 0, 0, NULL);

    // Установка направления осей координат: ось X вправо, ось Y вниз.
    SetViewportExtEx(g_hMemoryDC, 1, 1, NULL);
	
    PAINTSTRUCT paintStruct = {};

    // Получение контекста устройства, ассоциированного с основным окном.
    HDC hFormDC = BeginPaint(hWindow, &paintStruct);

    // Копирование изображения из контекста устройства памяти в контекст устройства окна.
    BitBlt(hFormDC, 0, 0, g_nWidth, g_nHeight, g_hMemoryDC, 0, 0, SRCCOPY);

    // Освобождение контекста устройства.
    EndPaint(hWindow, &paintStruct);

    DeleteObject(pen);
    DeleteObject(pen2);
}

VOID OnTimer(HWND hWindow, UINT uID)
{
    // Отправка приложению сообщения WM_PAINT.
    InvalidateRect(hWindow, NULL, FALSE);
}

VOID Quit(HWND hWindow, INT nMessage, INT nX, INT nY)
{
    if (nMessage == WM_MOUSEMOVE)
    {
        static INT nFirstX = nX;
        static INT nFirstY = nY;

        INT nCurrentX = nX;
        INT nCurrentY = nY;

        if (nCurrentX != nFirstX || nFirstY != nCurrentY)
        {
            EndDialog(hWindow, 0);
        }
    }
    else
    {
        EndDialog(hWindow, 0);
    }
}