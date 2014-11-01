// ���� windows.h �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows.
// ��� ���� ���������� ���������� �� ����������.
#include <windows.h>
#include <tchar.h>

// �������� ������� ���������, ������� ���������� ���������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("������ ��������");

// ����� ����� � ����������
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wcl;

	// 1. ����������� ������ ����
	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX
	// ������������ �� ����, ���� ���������� ������ �� ����������� ��� �� ���������
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ����
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra  = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ �������	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	// 2. ����������� ������ ����
	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// 3. �������� ����
	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	HWND hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	//��� ������ ����
		szClassWindow, // ��������� ����
		WS_OVERLAPPEDWINDOW,				// ����� ����
		// ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	// 4. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // ����������� ����

	// 5. ������ ����� ��������� ���������
	MSG lpMsg;
	while(GetMessage(&lpMsg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ���������
	{
		TranslateMessage(&lpMsg);	// ���������� ���������
		DispatchMessage(&lpMsg);	// ��������������� ���������
	}
	return lpMsg.wParam;
}	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0); // ������� ��������� WM_QUIT
		break;
	case WM_CREATE:
		{
			SECURITY_ATTRIBUTES sa;
			sa.nLength = sizeof(SECURITY_ATTRIBUTES); // ������ ���������
			sa.lpSecurityDescriptor = 0; // ������� ������ �� ���������
			sa.bInheritHandle = TRUE; // ���������� ������� ���� "����" - �����������

			HANDLE hHandle = CreateFile(
				TEXT("C:\\Cars.xml"), // ���� � �����
				GENERIC_READ, // ������ ������
				0, // ������ ����������� ������������� �����
				&sa, //�������� ������ ������� ���� �����
				OPEN_EXISTING, // �������� ������������� �����
				FILE_ATTRIBUTE_NORMAL, // ��������� ��� 
				NULL // ������ ������������ � ������-��������� ����������
				);

			if ( hHandle == INVALID_HANDLE_VALUE ){ //������ �������� �����
				MessageBox(0,L"OOPS!",L"Smth wrong!",0);
				return 0;
			}

			STARTUPINFO startin = {sizeof(STARTUPINFO)};
			PROCESS_INFORMATION info = {0};

			TCHAR cmd[20];
			//���������� ������� ���� ���������� ��������� �������� ����� ��������� ������
			wsprintf(cmd, TEXT("%s %d"), TEXT("child.exe"), hHandle);

			CreateProcess(
				NULL, // � �������� ����� ����� ��������� ������ ���������� ��������� ������� �� 2-�� ���������
				cmd, // ��������� ��������� ������, ����������, � ��� �����, ��� ������������ �����
				NULL, // �������� ������ �������� �� ���������
				NULL, // �������� ������ ������ �� ���������
				TRUE, // ������������ ������������ �������� ���� ���������
				0, // ����� ���������� �� ��������� - NORMAL_PRIORITY_CLASS 
				NULL, // ����� ��������� ����������� � ������������� �������� 
				NULL, // ������� ������� ����������� � ������������� �������� 
				&startin, //������ ����������� �������� ����, � ����� ������ � ��������� ����
				&info // ���������� � ���������� ��������
				);
			CloseHandle(hHandle); // ����������� ��������� ������� ���� �����
			CloseHandle(info.hThread); // ����������� ��������� ������� ���� ������
			CloseHandle(info.hProcess); // ����������� ��������� ������� ���� ��������

		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}