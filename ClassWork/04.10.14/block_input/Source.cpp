// ���� windows.h �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows.
// ��� ���� ���������� ���������� �� ����������.
#include <windows.h>

// ��������� ������������ ��� ANSI-���������, ��� � Unicode.
#include <tchar.h>

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
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ ������� (���������� ������ ��������!)
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������ - ������ ������� ����
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	// 2. ����������� ������ ����
	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// 3. �������� ����
	// ��������� ���� � ���������� hWnd ������������� ���������� ����

	HWND hWnd = CreateWindowEx(
		0,		// ����������� ����� ���� (WS_EX_ACCEPTFILES, WS_EX_CLIENTEDGE)
		szClassWindow,	//��� ������ ����
		TEXT("����� �������"), // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ���� (WS_HSCROLL | WS_VSCROLL)
		// ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����
		//0,0,rand()%200+200, rand()%200+200,
		CW_USEDEFAULT,    // �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		HWND_DESKTOP,			// ���������� ������������� ���� (HWND_DESKTOP)
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������


	// 4. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // ����������� ����

	// 5. ������ ����� ��������� ���������

	MSG lpMsg;
	while (GetMessage(&lpMsg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ��������� (���� �� ����� WM_QUIT)
	{ // �������� ����� ��������� �� ����� ����������
		TranslateMessage(&lpMsg);	// ���������� ��������� (����������� ��� ������ � �����������)
		DispatchMessage(&lpMsg);	// ��������������� ���������
	} // �������� ��������� ������� ���������
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	switch (uMessage)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		MessageBox(0, TEXT("����� �� ������� 1"), TEXT("����� ��������� 1"), MB_OKCANCEL | MB_ICONEXCLAMATION);
//		BlockInput(true);
//		ExitWindowsEx(EWX_LOGOFF, 0); //������������ ����������
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
