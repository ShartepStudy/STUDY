
#include "stdafx.h"
#include "ModlessDialog.h"

#define MAX_LOADSTRING 100

// ���� ���������
enum OurMessages 
{
	// �� �������� WM_USER ( 0x0400) ���������� �������� ��������, 
	// ������� ����� �������������� ��� ��������������
	// ����������� �������������  ���������.
	// �������� ������������� ��������������� ���������
	// �� ��������� 0x7FFF 
	UM_CHANGE = WM_USER
}; 

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int		rgb[3];			// ������������� ��� R-, G-, �-����������� ����� 
HWND	hModelessDlg;	// ���������� ������� ������ �����
HRGN	hWndRgn;		// ���������� ������� �������� ���� ��������� �����
HRGN	hDlgRgn;		// ���������� ������� ������� ��������� �����

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// �������� ���������� ���������
INT_PTR CALLBACK	ModelessDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MODLESSDIALOG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MODLESSDIALOG));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// ����� ��������� ������� ���� ����������, ���������� ������� �������
		// IsDialogMessage, ������� �� ���������� ������� � ����� ���������, 
		// �������� ���������� � ����������� �������.
		// ���� ������� IsDialogMessage ������� �� ������� ��������, 
		// �� ��������� ���������� �������� � ������������ �������� 
		// TranslateMessage, DispatchMessage ��� �� ������.
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) && 
			!IsDialogMessage(hModelessDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, 0);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MODLESSDIALOG);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{
		// ������������� ����������
	case WM_CREATE:
		// ������� ��������� ���� ��������� �����
		hModelessDlg = CreateDialog(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDD_MODELESS), hWnd, (DLGPROC)ModelessDlgProc); 

		// ������� ������� (������������ ��� ����������� ���� 
		// ���������� ��������� ����� ���� �������� ����, ��. UM_CHANGE)
		hWndRgn = CreateRectRgn(0,0,0,0);
		hDlgRgn = CreateRectRgn(0,0,0,0);
		// �������� ��������� ���� ���� ���� � ������������ 
		// � ���������� ���������� �������� ������������
		// (������ rgb).
		// ��������� �������� �������, �.�. ���� ������ ����������.
		// ����� ��������� ��������� - �������� �� ����������� WM_CREATE
		// ��������� UM_CHANGE ����� �� ����.
		SendMessage(hWnd, UM_CHANGE, 0, 0);
		// �������� ����� �� ���� ��������� ID_DIALOG_SHOW - 
		// ����������� ���� ������� ������ ����� � ������� 
		// ���������������� ������ � ����.
		SendMessage(hWnd, WM_COMMAND, ID_DIALOG_SHOW, 0);
		break;
		// UM_CHANGE - ������������� ���������, ��������� ����.
		// ��������� ������������� ���������� ��� ��������������
		// � ���������� �����  ��������� �����, �� ����� 
		// �������������� (� ������������) ����� ������� �����.
		// 
		// ������� �������������� �������� ���� � (������������)
		// �������: ����� ����� �������� ����������, �������� ��������
		// ���������.
		// 
		// ������� ���������, ������� ��������� ����������� ��������
		// (���������/���������� ������, ��������� ��������� � �.�.)
		// 
		// ���������� ��������� UM_CHANGE ��������� ��������
		// �������� ������������ �� ������� rgb � ��������� 
		// ���� ���� �������� ���� � ������������ � ����� ����������
	case UM_CHANGE:
		// �������� �������������, �����������
		// ���������� ����� �������� ����
		GetClientRect(hWnd, &rect);
		// ������� ������������� ������ 
		// �� ����������� ������ ��� ��������������
		hWndRgn = CreateRectRgnIndirect(&rect);
		// �������� �������� ���������� ������� ������ �����
		GetWindowRect(hModelessDlg, &rect);
		// ������������� ���������� � ������������ ������� �������� ����
		MapWindowPoints(0, hWnd, (POINT*)&rect, 2);

		// ������� ������, ��������������� ���� �������.
		hDlgRgn = CreateRectRgnIndirect(&rect);
		// �������� �� ������� �������� ���� ������ �������
		CombineRgn(hWndRgn, hWndRgn, hDlgRgn, RGN_DIFF);
		//  � hWndRgn ��������� ������ ���������� ����:
		//	+-----------------+
		//  |   +----+        |   
		//  |   |    |        |
		//  |   |    |        |
		//  |   +----+        |
		//  +-----------------+

		// ������ �������� ���� ��� ����� ����, ��� ���� ����������
		// ��������� ������ ����
		SetClassLong(hWnd, GCL_HBRBACKGROUND, 
			(LONG)CreateSolidBrush(RGB(rgb[0], rgb[1], rgb[2]))); 
		// �������������� ��� �������� ����
		// �������� � ��������� ����� ������������� ����� ��������� 
		// �������� ������� ��� ��������� ����� �������� ����
		// (�� ������� ������������� ��������� �������,
		// ���������� ��������).
		InvalidateRgn(hWnd, hWndRgn, TRUE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			// ��������� ID_DIALOG_SHOW ������������ ������� ���� Dialog -> Show
		case ID_DIALOG_SHOW:
			// ���������� ���� �������
			ShowWindow(hModelessDlg, SW_SHOW);
			// �������� ��������� ����� ����
			CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), ID_DIALOG_SHOW,
				ID_DIALOG_HIDE, ID_DIALOG_SHOW, MF_BYCOMMAND);
			break;			
			// ��������� ID_DIALOG_HIDE ������������ ������� ���� Dialog -> Hide
		case ID_DIALOG_HIDE:
			// ������ ���� �������
			ShowWindow(hModelessDlg, SW_HIDE);
			// �������� ��������� ����� ����
			CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), ID_DIALOG_SHOW, 
				ID_DIALOG_HIDE, ID_DIALOG_HIDE, MF_BYCOMMAND);
			break;	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		// ������� �������
		DeleteObject(hWndRgn);
		DeleteObject(hDlgRgn);
		DestroyWindow(hModelessDlg); 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ��������� ��������� ��������� ��� ����������� ����
INT_PTR CALLBACK ModelessDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// �������� ����������� ����� ���������
	HWND hRed	 = GetDlgItem(hDlg, IDC_RED); 
	HWND hGreen  = GetDlgItem(hDlg, IDC_GREEN); 
	HWND hBlue	 = GetDlgItem(hDlg, IDC_BLUE); 
	// ���������� �������� ������ ���������, ��. WM_VSCROLL
	HWND hCtrl; 
	// ������ ����������� �����:
	// 0 - �������� �������;
	// 1 - �������;
	// 2 - �����
	int  index;

	switch (message)
	{
		// ������������� �������
	case WM_INITDIALOG:
		// ������ �������� ���������� (0 - 255) ��� ������ �� ����� ���������
		SetScrollRange(hRed, SB_CTL, 0, 255, FALSE); 
		SetScrollRange(hGreen, SB_CTL, 0, 255, FALSE); 
		SetScrollRange(hBlue, SB_CTL, 0, 255, FALSE); 
		break;
	case WM_COMMAND:
		// ��� ����������� ��������� IDOK � IDCANCEL
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			// ���������� ��������� ID_DIALOG_HIDE �������� ����
			// ���������� ID_DIALOG_HIDE ������� ������
			// � ������� ����� ���� Dialog -> Hide
			SendMessage(GetParent(hDlg), WM_COMMAND, ID_DIALOG_HIDE, 0);
			return (INT_PTR)TRUE;
		}
		break;
		// ��������� ��������� �� ����� ���������
	case WM_VSCROLL: 
		// ��������� �� lParam ���������� ������ ���������,
		// ����������� ���������
		hCtrl = (HWND)lParam; 
		// �������������� IDC_RED, IDC_GREEN, IDC_BLUE 
		// � ��������� ����� ����������� �� �����������,
		// ��� ���� �������� ������������ ��������������
		// �� ������� ��������� �������� �����������.
		// ��� ��������� �� �������������� ������ ���������
		// �������� ����� ��������� �����:
		// index = �������������_������_��������� - IDC_RED
		index = GetDlgCtrlID(hCtrl) - IDC_RED;
		switch(LOWORD(wParam))
		{ 
		case SB_LINEUP: // ��������� �� ������ �����
			// ��������� �������� ������������ �� �������
			// � ������ �� ���� ���� ���������� ������������� �����
			rgb[index] = max(0, rgb[index] - 1); 
			break; 
		case SB_LINEDOWN: // ��������� �� ������ ����
			// ����������� �������� ������������ �� �������
			// � ������ �� 255, ���� ���������� ����� ������ 255
			rgb[index] = min(255, rgb[index] + 1); 
			break; 
		case SB_PAGEUP: // ��������� �� �������� �����
			// ���������� ���������� �� ������ �����
			rgb[index] = max(0, rgb[index] - 15); 
			break; 
		case SB_PAGEDOWN: // ��������� �� �������� ����
			// ���������� ���������� �� ������ ����
			rgb[index] = min(255, rgb[index] + 15); 
			break;
		case SB_THUMBTRACK: // ��������� �������������� ������ ������ ���������
			// ������������ ��������� ������ � �������� ������������
			rgb[index] = HIWORD(wParam); 
			break; 
		}
		// ������������ ������ ��������� � ����������� ������ ��� �������
		SetScrollPos(hCtrl, SB_CTL, rgb[index], TRUE); 
		// �������� ������������� ���� �� ��������� ����� ����
		// ����� ��������� ��������� ������������ ���� ������� ���� 
		// ������� ���� � ������������ �� ���������� � ������� rgb 
		SendMessage(GetParent(hDlg), UM_CHANGE, 0, 0); 
		break; 
		//----------------------------------------------------------------------
	default:
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)TRUE;
}
