#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;
HHOOK hHook;

CMyDialog::CMyDialog()
{
	ptr = this;
}

/*
����� ���������� �������� ��������� ������� ����������� �������� �� ����, ��� ��� ������ �� ����������. 
��� �������-����������� ����� ����� ����������� �� �������, �������� ��� �������� ��.
������ - ���-������� ��� ��������� ���� ������� ���� ��� ����������. 
����� Windows ������ �������� ���-�������, ��� ������� ������ ���� �����������, �.�. ����������� � ����. 
������������ ����� ��� ���������� ���-������� � ������-������ ���� ���������� ���������� ����. 
���� � ������ ���� ����������� ��������� ���-�������, Windows ��������� ������� ������� (������� �����), 
������ �������, ������������� ���������, ����������� � ������ �������, � ����� ������ ������� - � �� �����.
�������-������������ ����� ���� ���� � DLL ���� � ����������.
*/

CMyDialog::~CMyDialog()
{
	/*
	BOOL UnhookWindowsHookEx( - ������� ������������ ���
	HHOOK hhk � ���������� ���������� ����
	);
	*/
	UnhookWindowsHookEx(hHook);
}

LRESULT CALLBACK MouseProc(int idCode, WPARAM wParam, LPARAM lParam)
{
	/*
		���� ������ �������� ����� HC_ACTION - ��������� ����� ������� �� �������, �.�. ���� ���-������� ������ ��� ����������.
		HC_NOREMOVE - ��������� �� ����� ������� �� ������� � ��� ����� �������� ������� CallNextHookEx ��� ���������� ���������.
		wParam - ������������� ���������
		lParam - ��������� �� ��������� MOUSEHOOKSTRUCT

		typedef struct {
		POINT pt; - ���������� ������� ���� � �������� �����������
		HWND hwnd; - ���������� ����, �������� ������ ���������
		UINT wHitTestCode; - ���������� � ����� ������� ���� ��� ������ ����
		ULONG_PTR dwExtraInfo; - ����������, ������� ������� �� ���������.
		} MOUSEHOOKSTRUCT, *PMOUSEHOOKSTRUCT;
		*/

	MOUSEHOOKSTRUCT*ms = (MOUSEHOOKSTRUCT*)lParam;
	if (idCode == HC_ACTION)
	{
		if (wParam == WM_RBUTTONDOWN || wParam == WM_NCRBUTTONDOWN)
		{
			SetWindowText(ms->hwnd, "������ ������");
		}
		else if (wParam == WM_LBUTTONDOWN || wParam == WM_NCLBUTTONDOWN)
		{
			SetWindowText(ms->hwnd, "����� ������");
		}
		else if (wParam == WM_LBUTTONDBLCLK || wParam == WM_NCLBUTTONDBLCLK)
		{
			SetWindowText(ms->hwnd, "������� ������");
		}
		return 0;
	}

	/*
		������� ���������� ��������� ������� ��������� � ������� �������.
		LRESULT CallNextHookEx(
		HHOOK hhk,- ���������� ������� ������� ���������, ������������� SetWindowsHookEx
		int nCode,
		WPARAM wParam,
		LPARAM lParam
		);
		������������ �������� - ��, ��� ����� ��������� ������� ���������
		*/

	return CallNextHookEx(hHook, idCode, wParam, lParam);
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	hHook = SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
	/*
	������������� ������� ��������� ��������� Windows.

	HHOOK SetWindowsHookEx(
	int idHook,
	HOOKPROC lpfn,
	HINSTANCE hMod,
	DWORD dwThreadId
	);
	idHook - ��� ������� ��������� (����� ����)
	lpfn - ��������� �� ������� ���������. ��������� ������� ������� ������� �� ����.
	hMod - ���������� ������, ����������� ���-�������.
	��� ��������� ���� �� ����� � ������� �������� ���� �������� ������ ���� NULL.
	� ���� ������ ������� ��������� ������ ���� ���������� ������ ����, ���������� � ������� ���������.
	��� ��������� ���� ��� ���� ������� ��� ��� ������ � ������ ��������,
	����� ������������ ���������� DLL, ���������� �������-�����������.

	dwThreadId - ������������� ������, ��� �������� ��������������� ���.
	���� ���� ������������� ���������, ������������� ���-������� �����
	���������� ������ � ��������� ���������� ������.
	���� ������������� ����� ����, ������������� ������� ����� ��������� ������� ��������� �
	����� ���� ������� � ��������� ������ ������ � �������.
	� ���� ������ ������� ��������� ������ ���� ���������� � DLL.

	� ������ ������ ������� ���������� ���������� ������� ���������, ����� - 0.

	���������� ��� DLL ����� ������������ ������� GetCurrentThreadId ��� ���������
	�������������� �������� ������.
	DWORD WINAPI GetCurrentThreadId(void);

	���������� ��� DLL ����� ������������ ������� GetWindowThreadProcessId ��� ���������
	�������������� ������ ������ ��������.

	DWORD GetWindowThreadProcessId(
	HWND hWnd, //���������� ����, ������� ���� ������� ��������� ���������
	LPDWORD lpdwProcessId  // ��������� �� ����������, ���� ��������� ������������� ��������
	);

	*/
}


BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	case WM_INITDIALOG:
		ptr->OnInitDialog(hWnd);
		break;
	}
	return 0;
}