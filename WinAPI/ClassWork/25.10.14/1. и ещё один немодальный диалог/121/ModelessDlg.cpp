#include "ModelessDlg.h"

CModelessDialog* CModelessDialog::ptr = NULL;
HWND CModelessDialog::hAddDialog = NULL;

CModelessDialog::CModelessDialog(void)
{
	ptr = this;
}

CModelessDialog::~CModelessDialog(void)
{
	
}

void CModelessDialog::Cls_OnClose(HWND hwnd)
{
	// ��������� ����������� ���������� ����
	DestroyWindow(hwnd); 
	hAddDialog = NULL;
}

BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("�������������� ����������� ������"));
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("�������� ������ �������� �������!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK)
	{
		TCHAR buffer[200];
		// �������� ����� � ���������� ���� �����
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), buffer, 200);
		// �������� ���������� ������������� (��������) ����
		HWND hParent = GetParent(hwnd);
		// �������� ���������� ������� �������� �������
		HWND hStatic = GetDlgItem(hParent, IDC_STATIC1);
		// ���������� ����� �� ������� �������� �������
		SetWindowText(hStatic, buffer);
	}
	else if(id == IDCANCEL)
	{
		// ��������� ����������� ���������� ����
		DestroyWindow(hwnd); 
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CModelessDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
