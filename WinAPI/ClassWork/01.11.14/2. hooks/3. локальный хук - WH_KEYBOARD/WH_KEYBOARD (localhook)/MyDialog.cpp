#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;
HHOOK hHook;

CMyDialog::CMyDialog()
{
	ptr = this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	hStatic = GetDlgItem(hDialog, IDC_STATIC1);
}

LRESULT CALLBACK KeyboardProc(int idCode, WPARAM wParam, LPARAM lParam)
{
	/*
		idCode - ���� �������� ����� HC_ACTION, �� ��������� ������ ���������� HOOK,
		� ��������� ������ (���� < 0) ��������� ����� �������� ������� CallNextHookEx
		��� ���������� ���������, � ���������� ��������, ���������� �� ���� �������.
		wParam - ��� ����������� �������
		lParam - ��������� ����������, ����-���, 31 ��� - ���� ������, �� 1, ����� 0.
		*/
	if (HC_ACTION == idCode)
	{
		HWND hWnd = GetFocus();
		static char buf[40], text[65536];
		GetClassName(hWnd, buf, 40);
		if (lstrcmpi(buf, "EDIT") == 0 && (lParam & 0x80000000)) // ������� ��������!
		{
			if (wParam <= 32) // ������������ ������
			{
				wsprintf(buf, "0X%X", wParam);
			}
			else
			{
				if (!(wParam >= 'A' && wParam <= 'Z'))
					wsprintf(buf, "%c", wParam);
				else
				{
					short shift = GetKeyState(VK_SHIFT); // ���� ������� ��� ����� 1, �� ������� ������
					short caps = GetKeyState(VK_CAPITAL); // ���� ������� ��� ����� 1, �� ������� �����������
					if ((shift & 0x8000) && !(caps & 1) || !(shift & 0x8000) && (caps & 1))
					{
						wsprintf(buf, "%c", wParam);
					}
					else
					{
						wsprintf(buf, "%c", tolower(wParam));
					}
				}
			}
			lstrcat(text, buf);
			HWND hDialog = GetParent(hWnd);
			HWND hSt = GetDlgItem(hDialog, IDC_STATIC1);
			SetWindowText(hSt, text);
		}
	}
	return CallNextHookEx(hHook, idCode, wParam, lParam);
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if (LOWORD(wp) == IDC_BUTTON1)
	{
		hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, GetCurrentThreadId());
	}
	else if (LOWORD(wp) == IDC_BUTTON2)
	{
		UnhookWindowsHookEx(hHook);
	}
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
	case WM_COMMAND:
		ptr->OnCommand(wp, lp);
		break;
	}
	return 0;
}