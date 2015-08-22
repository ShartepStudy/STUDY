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
		wsprintf(szBuf, "Ошибка %d: %s", dwError, lpMsgBuf);
		MessageBox(0, szBuf, "Сообщение об ошибке", MB_OK | MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}


void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{

	if (LOWORD(wp) == IDC_BUTTON1)
	{
		/*
		Данная функция загружает DLL в адресное пространство процесса и возвращает дескриптор DLL.
		HMODULE LoadLibraryEx(
		LPCTSTR lpLibFileName, // путь к DLL или EXE-модулю
		HANDLE hFile, // не используется
		DWORD dwFlags // набор флагов
		LOAD_LIBRARY_AS_DATAFILE - система отображает файл в адресное пространство процесса, как файл данных
		);
		*/

		HMODULE hMod = LoadLibraryEx("DLL(Resource).dll", 0, LOAD_LIBRARY_AS_DATAFILE);
		if (!hMod)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		Находит ресурс с заданным именем в указанном модуле.
		Это может быть DLL либо EXE-файл. Если указать 0 - поиск в текущем модуле.
		Возвращается дескриптор ресурса в файле ресурса либо 0
		HRSRC FindResource(
		HMODULE hModule, // дескриптор модуля
		LPCTSTR lpName, // имя ресурса
		LPCTSTR lpType // тип ресурса
		);
		*/

		HRSRC src1 = FindResource(hMod, MAKEINTRESOURCE(106), "IMAGE");
		if (!src1)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		Загружает ресурс, найденный функцией FindResource.
		Возвращается дескриптор блока памяти, содержащего загруженный ресурс либо 0

		HGLOBAL LoadResource(
		HMODULE hModule, // дескриптор модуля, содержащего ресурс
		HRSRC hResInfo // дескриптор ресурса в файле ресурса
		);
		*/

		HGLOBAL h1 = LoadResource(hMod, src1);
		if (!h1)
		{
			MessageAboutError(GetLastError());
			return;
		}

		/*
		Функция блокирует ресурс, загруженный в память функцией LoadResource,
		и возвращает указатель на соответствующий адрес блока памяти.
		LPVOID LockResource(
		HGLOBAL hResData  // дескриптор ресурса, который необходимо заблокировать
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
		Возвращает размер ресурса в байтах
		DWORD SizeofResource(
		HMODULE hModule, // дескриптор модуля, содержащего ресурс
		HRSRC hResInfo // дескриптор ресурса, найденного функцией FindResource
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
		MessageBox(hDialog, "Сохранение ресурса в файл завершено!", "Ресурсы", MB_OK);

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