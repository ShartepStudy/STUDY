#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog(void)
{
	ptr=this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog=h;
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
		wsprintf(szBuf,"ќшибка %d: %s",dwError, lpMsgBuf); 
		MessageBox(0 ,szBuf, "—ообщение об ошибке", MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf);
	}
}

/*
ƒл€ выгрузки dll из пам€ти используетс€ 
EXTERN BOOL __FUnloadDelayLoadedDLL2(
LPCSTR szDll Ц название выгружаемой dll (им€ должно совпадать с именем файла на жестком диске)
) 
*/

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if (LOWORD(wp) == IDC_BUTTON1)
	{
		MessageInfo("Hello from DLL");
		if (!__FUnloadDelayLoadedDLL2("implicit_linking.dll"))
		{
			MessageAboutError(GetLastError());
			return;
		}
		MessageInfo("Hello from DLL");
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