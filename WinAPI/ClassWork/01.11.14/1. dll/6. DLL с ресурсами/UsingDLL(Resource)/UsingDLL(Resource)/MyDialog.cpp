#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog(void)
{
	ptr = this;
	count = 1;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	hStatic = GetDlgItem(hDialog, IDC_STATIC1);
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	CHAR szBuf[300];
	BOOL fOK = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
		);
	if (lpMsgBuf != NULL)
	{
		wsprintf(szBuf, "������ %d: %s", dwError, lpMsgBuf);
		MessageBox(0, szBuf, "��������� �� ������", MB_OK | MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}


void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{

	if (LOWORD(wp) == IDC_BUTTON1)
	{
		/*
		������ ������� ��������� DLL � �������� ������������ �������� � ���������� ���������� DLL.
		HMODULE LoadLibraryEx(
		LPCTSTR lpLibFileName, // ���� � DLL ��� EXE-������
		HANDLE hFile, // �� ������������
		DWORD dwFlags // ����� ������
		LOAD_LIBRARY_AS_DATAFILE - ������� ���������� ���� � �������� ������������ ��������, ��� ���� ������
		);
		*/

		HMODULE hMod = LoadLibraryEx("DLL(Resource).dll", 0, LOAD_LIBRARY_AS_DATAFILE);
		if (!hMod)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		������� ������ � �������� ������ � ��������� ������.
		��� ����� ���� DLL ���� EXE-����. ���� ������� 0 - ����� � ������� ������.
		������������ ���������� ������� � ����� ������� ���� 0
		HRSRC FindResource(
		HMODULE hModule, // ���������� ������
		LPCTSTR lpName, // ��� �������
		LPCTSTR lpType // ��� �������
		);
		*/

		HRSRC src1 = FindResource(hMod, MAKEINTRESOURCE(106), "IMAGE");
		if (!src1)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		��������� ������, ��������� �������� FindResource.
		������������ ���������� ����� ������, ����������� ����������� ������ ���� 0

		HGLOBAL LoadResource(
		HMODULE hModule, // ���������� ������, ����������� ������
		HRSRC hResInfo // ���������� ������� � ����� �������
		);
		*/

		HGLOBAL h1 = LoadResource(hMod, src1);
		if (!h1)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		������� ��������� ������, ����������� � ������ �������� LoadResource,
		� ���������� ��������� �� ��������������� ����� ����� ������.
		LPVOID LockResource(
		HGLOBAL hResData  // ���������� �������, ������� ���������� �������������
		);
		*/
		
		void * ptr1 = LockResource(h1);
		if (!ptr1)
		{
			MessageAboutError(GetLastError());
			return;
		}
		FILE * f1 = fopen("picture.jpg", "wb");
		if (!f1)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		���������� ������ ������� � ������
		DWORD SizeofResource(
		HMODULE hModule, // ���������� ������, ����������� ������
		HRSRC hResInfo // ���������� �������, ���������� �������� FindResource
		);
		*/

		fwrite(ptr1, 1, SizeofResource(hMod, src1), f1);
		fclose(f1);

		HRSRC src2 = FindResource(hMod, MAKEINTRESOURCE(112), "GIF");
		if (!src2)
		{
			MessageAboutError(GetLastError());
			return;
		}
		HGLOBAL h2 = LoadResource(hMod, src2);
		if (!h2)
		{
			MessageAboutError(GetLastError());
			return;
		}
		void * ptr2 = LockResource(h2);
		if (!ptr2)
		{
			MessageAboutError(GetLastError());
			return;
		}
		FILE * f2 = fopen("picture.gif", "wb");
		if (!f2)
		{
			MessageAboutError(GetLastError());
			return;
		}
		fwrite(ptr2, 1, SizeofResource(hMod, src2), f2);
		fclose(f2);
		FreeLibrary(hMod);
		MessageBox(hDialog, "���������� ������� � ���� ���������!", "�������", MB_OK);

	}
	else if (LOWORD(wp) == IDC_BUTTON2)
	{
		HMODULE hMod = LoadLibrary("cards.dll");
		if (!hMod)
		{
			MessageAboutError(GetLastError());
			return;
		}
		if (count > 65)
			count = 1;
		HBITMAP hBitmap = LoadBitmap(hMod, MAKEINTRESOURCE(count++));
		if (!hBitmap)
		{
			MessageAboutError(GetLastError());
			return;
		}
		SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));
		FreeLibrary(hMod);
	}

	else if (LOWORD(wp) == IDC_BUTTON3)
	{
		HMODULE hMod = LoadLibrary("DLL(Resource).dll");
		if (!hMod)
		{
			MessageAboutError(GetLastError());
			return;
		}
		static int count = 107;
		if (count > 111)
			count = 107;
		HBITMAP hBitmap = LoadBitmap(hMod, MAKEINTRESOURCE(count++));
		if (!hBitmap)
		{
			MessageAboutError(GetLastError());
			return;
		}
		SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));
		FreeLibrary(hMod);
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