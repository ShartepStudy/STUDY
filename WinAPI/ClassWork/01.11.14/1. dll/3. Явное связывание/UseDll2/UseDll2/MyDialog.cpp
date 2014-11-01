#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog(void)
{
	ptr = this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf=NULL;
	CHAR szBuf[300]; 
	BOOL fOK=FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM
		|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL 
		);
	if(lpMsgBuf!=NULL)
	{
		wsprintf(szBuf,"������ %d: %s",dwError, lpMsgBuf); 
		MessageBox(0 ,szBuf, "��������� �� ������", MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf);
	}
}

/*
��� ����� ���������� ���������� "�� �����" ����� ������ dll�����. 
������� ������ ���������� �� �������� ������� � ���, ��� dll����� ����������� ������ �����, 
����� ��� ����������. � ����������� � ����������� �� ���������� ������������.

HMODULE LoadLibrary( - ��������� dll����� � ��. ������������ ���������� dll������.
  LPCTSTR lpFileName � ���� � dll������
);

BOOL FreeLibrary( - ��������� dll����� �� ��.
  HMODULE hModule � ���������� dll������
);

FARPROC GetProcAddress(- ���������� ����� ������� ��� ���������� �� ����������� dll
  HMODULE hModule, - ���������� dll������
  LPCSTR lpProcName � ��� ��������� ������� ��� ����������.
);
FARPROC � ����������� ��� ��� ����������� ��������� �� �������.

*/

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	switch(LOWORD(wp))
	{
		case IDC_BUTTON1:
		{
			HMODULE hMod = LoadLibrary("implicit_linking.dll");
			if(!hMod)
			{
				MessageAboutError(GetLastError());
				return;
			}
			//void (*ptr)(char *);
			//ptr = (void (*)(char*)) GetProcAddress(hMod,"MessageInfo");

			auto ptr = (void (*)(char*)) GetProcAddress(hMod, "MessageInfo");

			if(!ptr)
			{
				MessageAboutError(GetLastError());
				return;
			}
			ptr("����� ������� MessageInfo �� ���������������� ����������");
			FreeLibrary(hMod);
		}
		break;
		case IDC_BUTTON2:
			{
				HMODULE hMod = LoadLibrary("implicit_linking.dll");
				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				void (*ptr)(int &);
				ptr = (void (*)(int &)) GetProcAddress(hMod,"Ref");
				if(!ptr)
				{
					MessageAboutError(GetLastError());
					return;
				}
				int N = 10;
				ptr(N);
				char str[100];
				wsprintf(str,"����� ������� Ref �� ���������������� ����������.\n����� �������� ���������� N: %d",N);
				MessageBox(hDialog, str, "����� ����������", MB_OK | MB_ICONINFORMATION);
				int * pCounter = (int *) GetProcAddress(hMod, "counter");
				wsprintf(str,"�������� ���������� counter: %d",*pCounter);
				MessageBox(hDialog, str, "����� ����������", MB_OK | MB_ICONINFORMATION);
				FreeLibrary(hMod);
			}
			break;
		case IDC_BUTTON3:
			{
				HMODULE hMod = GetModuleHandle("user32.dll");
				// �������, ������� ���������� ��� �� ����� �����, ��� � LoadLibrary, - ��� GetModuleHandle.
				// ���� �� ������ ��� DLL ��� ��������� � ������ � �� ���������, �� ����� ������� GetModuleHandle
				// ������ LoadLibrary. ������, � ������� �� LoadLibrary, ��� ������� �� ����������� ������� ������
				// �� DLL, ������� ���������� ��������� �������� DLL ������ ���������� � �� ����� ����� �� � ���
				// ���������.

				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				int  (__stdcall*ptr)(HWND, LPCTSTR);
				(FARPROC&)ptr = GetProcAddress(hMod, "SetWindowTextA");
				ptr(hDialog, "����� ������� SetWindowText �� ���������� user32.dll");
				FreeLibrary(hMod);
			}
			break;
		case IDC_BUTTON4:
			{
				typedef void (*MyPrototype)(char*);
				HMODULE hMod = LoadLibrary("implicit_linking.dll");
				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				MyPrototype ptr;
				ptr = (MyPrototype) GetProcAddress(hMod,"MessageInfo");
				ptr("����� ������� MessageInfo �� ���������������� ����������");
				FreeLibrary(hMod);
			}
			break;
		case IDC_BUTTON5:
			{
				HMODULE hMod = GetModuleHandle("user32.dll");
				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				int  (__stdcall*ptr)(HWND, LPCTSTR, LPCTSTR, UINT); 
				(FARPROC&)ptr = GetProcAddress(hMod, MAKEINTRESOURCE(2093)); //MessageBoxA
				ptr(NULL,"����� ������� MessageBox �� ���������� user32.dll","Message",MB_OK);
				FreeLibrary(hMod);
			}
			break;
		case IDC_BUTTON6:
			{
				HMODULE hMod = GetModuleHandle("user32.dll");
				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				int  (__stdcall*ptr)(HWND, INT_PTR); 
				(FARPROC&)ptr = GetProcAddress(hMod, "EndDialog"); //EndDialog
				ptr(hDialog, 0);
				FreeLibrary(hMod);
			}
			break;

	}
}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd,UINT mes,WPARAM wp,LPARAM lp)
{
	switch(mes)
	{
		case WM_CLOSE:
			EndDialog(hWnd,0);
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