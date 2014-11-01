#include "MyDialog.h"

#pragma comment (lib, "implicit_linking(class).lib")

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog()
{
	ptr = this;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	SetTimer(hDialog, 1, 1000, 0);
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if(LOWORD(wp) == IDC_BUTTON1)
	{
		clk.SetTime(18, 50, 30);
	}
}

void CMyDialog::OnTimer()
{
	char* ptr = clk.Tick();
	SetWindowText(hDialog, ptr);
}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch(mes)
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
		case WM_TIMER:
			ptr->OnTimer();
			break;
	}
	return 0;
}