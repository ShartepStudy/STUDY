
#include "stdafx.h"
#include "ModlessDialog.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND	hModelessDlg;	// ���������� �������

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

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MODLESSDIALOG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// ����� ��������� ������� ���� ����������, ���������� ������� �������
		// IsDialogMessage, ������� �� ���������� ������� � ����� ���������, 
		// �������� ���������� � ����������� �������.
		// ���� ������� IsDialogMessage ������� �� ������� ��������, 
		// �� ��������� ���������� �������� � ������������ �������� 
		// TranslateMessage, DispatchMessage ��� �� ������.
		if (!IsDialogMessage(hModelessDlg, &msg))
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
	HDC hdc;

	switch (message)
	{
		// ������������� ����������
	case WM_CREATE:
		// ������� ��������� ���� ��������� �����
		hModelessDlg = CreateDialog(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDD_MODELESS), hWnd, (DLGPROC)ModelessDlgProc); 

		//hModelessDlg = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
			//CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, GetModuleHandle(NULL), NULL);

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

	case WM_DESTROY:
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
	
	switch (message)
	{
		// ������������� �������
	case WM_INITDIALOG:
		
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
	
	default:
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)TRUE;
}
