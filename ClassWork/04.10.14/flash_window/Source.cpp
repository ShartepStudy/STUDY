// ���� windows.h �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows.
// ��� ���� ���������� ���������� �� ����������.
#include <windows.h>

// ��������� ������������ ��� ANSI-���������, ��� � Unicode.
#include <tchar.h>

// ��������� ������������ ������� time, ��� ��������� ��������� �����.
#include <time.h>

// �������� ������� ���������, ������� ���������� ���������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������");	// ��� ������ ����

// ����� ����� � ����������
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	// 1. ����������� ������ ����
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);	// ������ � ������ ��������� WNDCLASSEX
	// ������������ �� ����, ���� ������ ������ �� ����������� ��� �� ���������
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ���� (CS_DBLCLKS!)
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������, ��������� �� ������� WindowProc
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������ (���������� ������ ������!)
	// #include "resource.h" // ���������������� ������
	// HINSTANCE hIns=GetModuleHandle(0);
	// HICON hIcon=LoadIcon(hIns,MAKEINTRESOURCE(IDI_ICON1));
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ ������� (���������� ������ ��������!)
	// HCURSOR hCursor=LoadCursorFromFile(L"C:\\1.ani");
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������ - ������ ������� ����
	//wcl.hbrBackground=CreateSolidBrush (RGB(255,120,0)); // ����� ����
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	// 2. ����������� ������ ����
	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// 3. �������� ����
	// ��������� ���� � ���������� hWnd ������������� ���������� ����

	//srand(time(0));
	//wchar_t*s=new wchar_t[200];
	//int test=rand()%50;
	//_itow(test,s,10);

	HWND hWnd = CreateWindowEx(
		0,		// ����������� ����� ���� (WS_EX_ACCEPTFILES, WS_EX_CLIENTEDGE)
		szClassWindow,	//��� ������ ����
		TEXT("������ ����!"), // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ���� (WS_HSCROLL | WS_VSCROLL)
		// ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����
		0, 0, rand() % 200 + 200, rand() % 200 + 200,
		//CW_USEDEFAULT,    // �-���������� ������ �������� ���� ����
		//CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		//CW_USEDEFAULT,	// ������ ����
		//CW_USEDEFAULT,	// ������ ����
		HWND_DESKTOP,			// ���������� ������������� ���� (HWND_DESKTOP)
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������


	// 4. ����������� ����
	FLASHWINFO info;
	info.cbSize = sizeof(info);
	info.hwnd = hWnd;
	info.dwFlags = FLASHW_ALL;
	info.dwTimeout = 0;
	info.uCount = 5;

	ShowWindow(hWnd, nCmdShow);
	FlashWindowEx(&info);

	UpdateWindow(hWnd); // ����������� ����

	/*#define SW_HIDE             0
	#define SW_SHOWNORMAL       1
	#define SW_NORMAL           1
	#define SW_SHOWMINIMIZED    2
	#define SW_SHOWMAXIMIZED    3
	#define SW_MAXIMIZE         3
	#define SW_SHOWNOACTIVATE   4
	#define SW_SHOW             5
	#define SW_MINIMIZE         6
	#define SW_SHOWMINNOACTIVE  7
	#define SW_SHOWNA           8
	#define SW_RESTORE          9
	#define SW_SHOWDEFAULT      10
	#define SW_FORCEMINIMIZE    11
	#define SW_MAX              11*/

	/* // ���������� ������� (�� �������)
	HMENU main_menu = CreateMenu();
	HMENU menu_help = CreatePopupMenu();
	HMENU menu_view = CreatePopupMenu();
	AppendMenu(main_menu, MF_STRING | MF_POPUP, (UINT)menu_view, L"��������");
	AppendMenu(main_menu, MF_STRING | MF_POPUP, (UINT)menu_help, L"�������");
	AppendMenu(menu_help, MF_STRING, 1001, L"� ���������...");
	AppendMenu(menu_view, MF_STRING, 1002, L"�����");
	AppendMenu(menu_view, MF_STRING, 1003, L"�������");
	SetMenu(hWnd, main_menu);
	*/

	// 5. ������ ����� ��������� ���������

	MSG lpMsg;
	while (GetMessage(&lpMsg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ��������� (���� �� ����� WM_QUIT)
	{ // �������� ����� ��������� �� ����� ����������
		TranslateMessage(&lpMsg);	// ���������� ��������� (����������� ��� ������ � �����������)
		DispatchMessage(&lpMsg);	// ��������������� ���������
	} // �������� ��������� ������� ���������
	return lpMsg.wParam;
}

// ������� ���������� ��, �� ����������!
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0); // ������� ��������� WM_QUIT
		break;
	case WM_CLOSE:
		MessageBoxA(0, "Ha-Ha", "� �� ��������!", MB_OK);
		break;
	default:
		// ��� ���������, ������� �� �������������� � ������ ������� ������� 
		// ������������ ������� Windows �� ��������� �� ���������
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}