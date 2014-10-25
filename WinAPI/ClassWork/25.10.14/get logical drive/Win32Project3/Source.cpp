#include <windows.h>
#include <windowsX.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND hCombo;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

int gld; // ������� ����� ���������� ������
wchar_t str[200];

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		true;

	case WM_INITDIALOG:
		hCombo = GetDlgItem(hwnd, IDC_COMBO1);
    //MoveWindow(hCombo, 0, 0, 100, 500, true);
		gld = GetLogicalDrives();
		for(int i = 0, md = 1; i < gld; ++i, md *= 2)
		{
			if(gld & md)
			{
				wchar_t y = i + 65;
				wsprintf(str, TEXT("%c"), y);
				lstrcat(str, L": ");

				UINT uDT = GetDriveType(str);
				if(uDT == DRIVE_REMOVABLE)
				{
					lstrcat(str, L"(������� ����)");
				}

				else if(uDT == DRIVE_FIXED)
				{
					lstrcat(str, L"(Ƹ����� ����)");
				}

				else if(uDT == DRIVE_CDROM)
				{
					lstrcat(str, L"(CD-ROM)");
				}

				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) str);
			}
		}
	}
	return FALSE;
}