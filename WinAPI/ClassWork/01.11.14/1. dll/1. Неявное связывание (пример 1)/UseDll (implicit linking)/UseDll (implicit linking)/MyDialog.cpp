#include "MyDialog.h"

#include "implicit linking.h"

//#pragma comment (lib, "implicit_linking.lib")

/*

При неявном связывании:

1. Перенести dll, lib, h - файлы в папку этого проекта.
2. Для использования функции из dll  нужно подключить h - файл и lib – файл.
	
	Три способа подключения lib-файла.
	a. #pragma comment (lib, "FirstDll.lib")
	b. Подключить lib–файл, как файл в программу, через Solution Explorer.
	c. Подключить через опции проекта: Properties->Linker->Input->Additional Dependences (X)
*/

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog(void)
{
	ptr=this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
}

DWORD WINAPI Thread(LPVOID lp)
{
	MessageInfo("Привет от фонового потока!");
	return 0;
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if(LOWORD(wp) == IDC_BUTTON1)
	{
		MessageInfo("Привет от первичного потока!");
		CreateThread(0,0,Thread,0,0,0);
	}
	else if(LOWORD(wp)==IDC_BUTTON2)
	{
		int f = 12;
		Ref(f);
		char str[10];
		wsprintf(str, "%d", f);
		MessageInfo(str);
		wsprintf(str, "%d", counter);
		MessageInfo(str);
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