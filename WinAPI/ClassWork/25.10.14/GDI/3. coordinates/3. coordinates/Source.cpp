#define _USE_MATH_DEFINES

#include <cmath>
#include <tchar.h>
#include <Windows.h>
#include <WindowsX.h>

#include "resource.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")

BOOL CALLBACK DialogProcedure(HWND hWindow, UINT nMessage, WPARAM wParam, LPARAM lParam);
VOID OnClose(HWND hWindow);
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
		HANDLE_MSG(hWindow, WM_PAINT, OnPaint);
	}

	return FALSE;
}

VOID OnClose(HWND hWindow)
{
	EndDialog(hWindow, 0);
}

VOID OnPaint(HWND hWindow)
{
	PAINTSTRUCT paintStruct = {};

	// Получение контекста устройства.
	HDC hDC = BeginPaint(hWindow, &paintStruct);

	// Установка графического режима для данного контекста устройства, позволяющего выполнять 
	// мировые преобразования.
	SetGraphicsMode(hDC, GM_ADVANCED);
	// http://www.gornakov.com/articles/osnovy-programmirovaniya-trexmernoj-grafiki-v-directx-chast-iv-matrichnye-preobrazovaniya/

	// Создание сплошной кисти.
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

	// Выбор кисти в контекст устройства.
	SelectObject(hDC, hBrush);

	// Создание прозрачного пера.
	HPEN hPen = CreatePen(PS_NULL, 1, 0);

	// Выбор пера в контекст устройства.
	SelectObject(hDC, hPen);
	RECT rectangle = {};

	// Получение прямоугольника, охватывающего клиентскую область окна.
	GetClientRect(hWindow, &rectangle);

	// Установка начала координат области просмотра.
	SetViewportOrgEx(hDC, rectangle.right / 2, rectangle.bottom / 2, NULL);
	POINT points[] = { { 0, 0 }, { -50, -100 }, { 0, -200 }, { 50, -100 } };

	// Рисование многоугольника.
	Polygon(hDC, points, ARRAYSIZE(points));

	FLOAT fltAngle = (FLOAT)(2 * M_PI / 3) - 0.06f;

	// Заполнение матрицы преобразования.
	XFORM xf = {};
	xf.eM11 = cos(fltAngle);
	xf.eM12 = -sin(fltAngle);
	xf.eM21 = sin(fltAngle);
	xf.eM22 = cos(fltAngle);

	// Установка мирового преобразования.
	SetWorldTransform(hDC, &xf);

	// Рисование многоугольника.
	Polygon(hDC, points, ARRAYSIZE(points));

	fltAngle = -fltAngle;

	xf.eM11 = cos(fltAngle);
	xf.eM12 = -sin(fltAngle);
	xf.eM21 = sin(fltAngle);
	xf.eM22 = cos(fltAngle);

	// Установка мирового преобразования.
	SetWorldTransform(hDC, &xf);

	// Рисование многоугольника.
	Polygon(hDC, points, ARRAYSIZE(points));

	// Возврат первоначальных значений.
	ModifyWorldTransform(hDC, NULL, MWT_IDENTITY);

	// Освобождение кисти.
	DeleteObject(hBrush);

	// Освобождение пера.
	DeleteObject(hPen);

	// Освобождение контекста устройства.
	EndPaint(hWindow, &paintStruct);
}