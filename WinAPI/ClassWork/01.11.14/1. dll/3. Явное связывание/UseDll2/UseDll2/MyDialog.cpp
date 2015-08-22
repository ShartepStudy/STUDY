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
		wsprintf(szBuf,"Ошибка %d: %s",dwError, lpMsgBuf); 
		MessageBox(0 ,szBuf, "Сообщение об ошибке", MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf);
	}
}

/*
При явном связывании необходимо "на руках" иметь только dll–файл. 
Отличие явного связывания от неявного состоит в том, что dll–файл загружается только тогда, 
когда это необходимо. А выгружается в зависимости от требований программиста.

HMODULE LoadLibrary( - загружает dll–файл в ОП. Возвращается дескриптор dll–файла.
  LPCTSTR lpFileName – путь к dll–файлу
);

BOOL FreeLibrary( - выгружает dll–файл из ОП.
  HMODULE hModule – дескриптор dll–файла
);

FARPROC GetProcAddress(- возвращает адрес функции или переменной из загруженной dll
  HMODULE hModule, - дескриптор dll–файла
  LPCSTR lpProcName – имя требуемой функции или переменной.
);
FARPROC – специальный тип для обобщенного указателя на функцию.

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
			ptr("Вызов функции MessageInfo из пользовательской библиотеки");
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
				wsprintf(str,"Вызов функции Ref из пользовательской библиотеки.\nНовое значение переменное N: %d",N);
				MessageBox(hDialog, str, "Явное связывание", MB_OK | MB_ICONINFORMATION);
				int * pCounter = (int *) GetProcAddress(hMod, "counter");
				wsprintf(str,"Значение переменной counter: %d",*pCounter);
				MessageBox(hDialog, str, "Явное связывание", MB_OK | MB_ICONINFORMATION);
				FreeLibrary(hMod);
			}
			break;
		case IDC_BUTTON3:
			{
				HMODULE hMod = GetModuleHandle("user32.dll");
				// функция, которая возвращает тот же самый хендл, что и LoadLibrary, - это GetModuleHandle.
				// Если вы знаете что DLL уже загружена в память и не выгружена, то можно вызвать GetModuleHandle
				// вместо LoadLibrary. Однако, в отличие от LoadLibrary, эта функция не увеличивает счетчик ссылок
				// на DLL, поэтому становится возможной выгрузка DLL другой программой в то время когда вы с ней
				// работаете.

				if(!hMod)
				{
					MessageAboutError(GetLastError());
					return;
				}
				int  (__stdcall*ptr)(HWND, LPCTSTR);
				(FARPROC&)ptr = GetProcAddress(hMod, "SetWindowTextA");
				ptr(hDialog, "Вызов функции SetWindowText из библиотеки user32.dll");
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
				ptr("Вызов функции MessageInfo из пользовательской библиотеки");
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
				ptr(NULL,"Вызов функции MessageBox из библиотеки user32.dll","Message",MB_OK);
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