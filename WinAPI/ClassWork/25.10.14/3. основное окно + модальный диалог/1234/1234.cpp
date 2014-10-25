#include <windows.h>
#include "resource.h"

// ���������� ���������� ����
HWND hDlgModal;

// ��������� ��������� �������� ���� � ���������� ����������� �����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModal(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �������� �������� ����
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = L"�������� ����";

	//������������ ����� ����
	RegisterClass(&w);

	hwnd = CreateWindow(w.lpszClassName, w.lpszClassName, WS_OVERLAPPEDWINDOW, 10, 10, 290, 100, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// ���������� ������ �� ������� ����
	CreateWindow(L"Button", L"������� ��������� ������!", WS_CHILD | WS_VISIBLE, 10, 10, 250, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

	//��������� ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (hDlgModal == 0 || !IsDialogMessage(hDlgModal, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

//��������� �������� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	static HINSTANCE hInstance;
	switch (Message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lparam)->hInstance;
		break;
	case WM_PAINT:
		break;
	case WM_COMMAND:
		if (HIWORD(wparam) == BN_CLICKED) // ���� ���� ������ ������
		{
			switch (LOWORD(wparam))
			{ 			// � ��� ������ �������� ���������� ����
			case ID_BUTTON:
				// ������� ��������� ����
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProcModal);
				break;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}

BOOL CALLBACK DlgProcModal(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		// ��������� �������
		SetWindowText(hDlg, TEXT("��������� ������"));
		return TRUE;
	case WM_CLOSE:
		// ��������
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hDlg, L"�� ������� ������ ������ OK !", L"��������� ���������� ����", MB_OK);
			break;

		case IDCANCEL:
			MessageBox(hDlg, L"�� ������� ������ ������ Cancel !", L"��������� ���������� ����", MB_OK);
			//��������� ����
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}