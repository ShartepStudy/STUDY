
#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include "resource.h"

class CMainDialog
{
public:
	CMainDialog(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainDialog* ptr;
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
};

CMainDialog* CMainDialog::ptr = NULL;

CMainDialog::CMainDialog(void)
{
	ptr = this;
}

void CMainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl,
	UINT codeNotify)
{

	if (id == IDC_SAVE)
	{
		TCHAR FullPath[MAX_PATH] = { 0 };
		OPENFILENAME open = { sizeof(OPENFILENAME) };
		open.hwndOwner = hwnd;
		open.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0Microsoft Word Files(*.doc)\0*.doc\0 ");
		open.lpstrFile = FullPath;
		open.nMaxFile = MAX_PATH;
		open.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
		open.lpstrDefExt = TEXT("txt");
		if (GetSaveFileName(&open))
		{
			TCHAR str[300] = TEXT("�� ������� ��� ���������� ����:\n");
			_tcscat(str, FullPath);
			MessageBox(hwnd, str, TEXT("������ \"���������\""), MB_OK | MB_ICONINFORMATION);
		}
	}
	else if (id == IDC_OPEN)
	{
		TCHAR FullPath[MAX_PATH] = { 0 };
		OPENFILENAME open = { sizeof(OPENFILENAME) };
		open.hwndOwner = hwnd;
		open.lpstrFilter =
			TEXT("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0");
		open.lpstrFile = FullPath;
		open.nMaxFile = MAX_PATH;
		open.lpstrInitialDir = TEXT("C:\\");
		open.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		if (GetOpenFileName(&open))
		{
			TCHAR str[300] = TEXT("�� ������� ��� �������� ����:\n");
			_tcscat(str, FullPath);
			MessageBox(hwnd, str, TEXT("������ \"�������\""), MB_OK | MB_ICONINFORMATION);
		}
	}
}

BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine,
	int nCmdShow)
{
	CMainDialog dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, CMainDialog::DlgProc);
}
