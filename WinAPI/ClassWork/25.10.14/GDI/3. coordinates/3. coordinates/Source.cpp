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

	// ��������� ��������� ����������.
	HDC hDC = BeginPaint(hWindow, &paintStruct);

	// ��������� ������������ ������ ��� ������� ��������� ����������, ������������ ��������� 
	// ������� ��������������.
	SetGraphicsMode(hDC, GM_ADVANCED);
	// http://www.gornakov.com/articles/osnovy-programmirovaniya-trexmernoj-grafiki-v-directx-chast-iv-matrichnye-preobrazovaniya/

	// �������� �������� �����.
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

	// ����� ����� � �������� ����������.
	SelectObject(hDC, hBrush);

	// �������� ����������� ����.
	HPEN hPen = CreatePen(PS_NULL, 1, 0);

	// ����� ���� � �������� ����������.
	SelectObject(hDC, hPen);
	RECT rectangle = {};

	// ��������� ��������������, ������������� ���������� ������� ����.
	GetClientRect(hWindow, &rectangle);

	// ��������� ������ ��������� ������� ���������.
	SetViewportOrgEx(hDC, rectangle.right / 2, rectangle.bottom / 2, NULL);
	POINT points[] = { { 0, 0 }, { -50, -100 }, { 0, -200 }, { 50, -100 } };

	// ��������� ��������������.
	Polygon(hDC, points, ARRAYSIZE(points));

	FLOAT fltAngle = (FLOAT)(2 * M_PI / 3) - 0.06f;

	// ���������� ������� ��������������.
	XFORM xf = {};
	xf.eM11 = cos(fltAngle);
	xf.eM12 = -sin(fltAngle);
	xf.eM21 = sin(fltAngle);
	xf.eM22 = cos(fltAngle);

	// ��������� �������� ��������������.
	SetWorldTransform(hDC, &xf);

	// ��������� ��������������.
	Polygon(hDC, points, ARRAYSIZE(points));

	fltAngle = -fltAngle;

	xf.eM11 = cos(fltAngle);
	xf.eM12 = -sin(fltAngle);
	xf.eM21 = sin(fltAngle);
	xf.eM22 = cos(fltAngle);

	// ��������� �������� ��������������.
	SetWorldTransform(hDC, &xf);

	// ��������� ��������������.
	Polygon(hDC, points, ARRAYSIZE(points));

	// ������� �������������� ��������.
	ModifyWorldTransform(hDC, NULL, MWT_IDENTITY);

	// ������������ �����.
	DeleteObject(hBrush);

	// ������������ ����.
	DeleteObject(hPen);

	// ������������ ��������� ����������.
	EndPaint(hWindow, &paintStruct);
}