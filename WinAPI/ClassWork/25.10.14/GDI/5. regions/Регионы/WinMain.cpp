#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

HBRUSH g_hBrush = NULL;

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType);
BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam);
VOID OnLButtonDown(HWND hWindow, BOOL fDoubleClick, INT nX, INT nY, UINT uKeyFlags);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, INT nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure); 
}

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
    switch (nMessage)
    {
        HANDLE_MSG(hWindow, WM_CLOSE, OnClose);
        HANDLE_MSG(hWindow, WM_CTLCOLORDLG, OnCtlColor);
        HANDLE_MSG(hWindow, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hWindow, WM_LBUTTONDOWN, OnLButtonDown);
    }

    return FALSE;
}

VOID OnClose(HWND hWindow)
{
    DeleteObject(g_hBrush);

    EndDialog(hWindow, 0);
}

HBRUSH OnCtlColor(HWND hWindow, HDC hDC, HWND hChild, INT nType)
{
    HBRUSH hBrush = NULL;

	if (nType == CTLCOLOR_DLG)
    {
        hBrush = g_hBrush;
    }

    return hBrush;
}

BOOL OnInitDialog(HWND hWindow, HWND hFocus, LPARAM lParam)
{
    // Создание сплошную кисть.
    g_hBrush = CreateSolidBrush(RGB(255, 0, 255));

    // Создание эллиптического региона.
    HRGN hRegion1 = CreateEllipticRgn(0, 0, 200, 200);

    // Создание эллиптического региона.
    HRGN hRegion2 = CreateEllipticRgn(20, 20, 180, 180);

    // Создание региона-кольца, применяя операцию вычитания.
    CombineRgn(hRegion1, hRegion1, hRegion2, RGN_DIFF);

    // Создание прямоугольного региона.
    HRGN hRegion3 = CreateRectRgn(90, 80, 110, 120);

    // Создание прямоугольного региона.
    HRGN hRegion4 = CreateRectRgn(80, 90, 120, 110);

    // Комбинирование двух прямоугольных регионов, исключая общую область.
    CombineRgn(hRegion3, hRegion3, hRegion4, RGN_XOR);

    // Создание результирующего региона.
    CombineRgn(hRegion1, hRegion1, hRegion3, RGN_OR);

    // устанавливаем регион на главное окно
    SetWindowRgn(hWindow, hRegion1, TRUE);

    return TRUE;
}

VOID OnLButtonDown(HWND hWindow, BOOL fDoubleClick, INT nX, INT nY, UINT uKeyFlags)
{
	// Имитация нажатия левой кнопки мыши на заголовке это позволяет перетаскивать форму.
	SendMessage(hWindow, WM_NCLBUTTONDOWN, HTCAPTION, 0);
}