#include "MyDialog.h"
#define WM_KEYSTROKE (WM_USER + 755)

CMyDialog *CMyDialog::ptr;

HMODULE hModule;

typedef BOOL (*INSTALL)();
typedef BOOL (*REMOVE)();

CMyDialog::CMyDialog()
{
	ptr = this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	hButton1 = GetDlgItem(hDialog, IDC_BUTTON1);
	hButton2 = GetDlgItem(hDialog, IDC_BUTTON2);
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if (LOWORD(wp) == IDC_BUTTON1)
	{
		hModule = LoadLibrary("WH_KEYBOARD_DLL.dll");
		if (!hModule)
			return;
		INSTALL f = (INSTALL)GetProcAddress(hModule, "installhook");
		if (!f)
		{
			MessageBox(hDialog, "HOOK не был установлен!", "Клавиатурный HOOK", MB_OK | MB_ICONSTOP);
			FreeLibrary(hModule);
			return;
		}
		f();
		EnableWindow(hButton1, 0);
		EnableWindow(hButton2, 1);
	}
	else if (LOWORD(wp) == IDC_BUTTON2)
	{
		REMOVE f = (REMOVE)GetProcAddress(hModule, "removehook");
		if (!f)
		{
			MessageBox(hDialog, "HOOK не был удалён!", "Клавиатурный HOOK", MB_OK | MB_ICONSTOP);
			FreeLibrary(hModule);
			return;
		}
		f();
		FreeLibrary(hModule);
		EnableWindow(hButton2, 0);
		EnableWindow(hButton1, 1);
	}
}

void CMyDialog::OnKeyStroke(WPARAM wp, LPARAM lp)
{
	FILE * f = fopen("KeyLog.txt", "a+");
	if (!f)
		return;
	//получаем строку, описывающую название клавиши
	//в lp - находится код клавиши
	char buffer[20];
	GetKeyNameText(lp, buffer, 20); // Выбирает строку, содержащую имя клавиши по скэн-коду
	fputs(buffer, f);
	fclose(f);
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
	case WM_KEYSTROKE:
		ptr->OnKeyStroke(wp, lp);
		break;
	}
	return 0;
}