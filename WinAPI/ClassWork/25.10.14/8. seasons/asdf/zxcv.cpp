#include <windows.h>
#include <windowsX.h>
#include "resource.h"

class SeasonsDlg
{
public:
	SeasonsDlg(void);

	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static SeasonsDlg* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hList, hCombo, hCheck, hEdit;
};

SeasonsDlg* SeasonsDlg::ptr = NULL;

SeasonsDlg::SeasonsDlg(void)
{
	ptr = this;
}

void SeasonsDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	SeasonsDlg dlg;

	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, SeasonsDlg::DlgProc);
}

BOOL SeasonsDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	// ������� ����������� ��������� ����������
	hCombo = GetDlgItem(hwnd, IDC_SEASONS);
	hList = GetDlgItem(hwnd, IDC_MONTH);
	hEdit = GetDlgItem(hwnd, IDC_DAYS);
	hCheck = GetDlgItem(hwnd, IDC_LEAF);

	// !!! ������ ����� ����� !!!
	MoveWindow (hCombo, 0, 0, 110, 500, true);
	//////////////////////////////////////////

	// ��������� ������� ���� � ComboBox
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("����")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("�����")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("����")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("�����")));
	return TRUE;
}

void SeasonsDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// ������� CBN_SELCHANGE ����������� ������ ���������� � ��� ������, ����� ���������� ����� ������� � ������
	if(id == IDC_SEASONS && codeNotify == CBN_SELCHANGE)
	{
		// ������� ListBox
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		// ������� ������ ���������� �������� ComboBox
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0); 
		switch(index)
		{
		case 0:
			// ��������� � ListBox �������� ������ � ���������� ������ ������������ ��������
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("�������")));
			// ������ �������� ������ � ������������ �����, ������������ ���������� ���� � ������
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("������")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("�������")));
			SendMessage(hList, LB_SETITEMDATA, index, 28);
			break;

		case 1:
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("����")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("������")));
			SendMessage(hList, LB_SETITEMDATA, index, 30);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("���")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			break;

		case 2:
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("����")));
			SendMessage(hList, LB_SETITEMDATA, index, 30);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("����")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("������")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			break;

		case 3:
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("��������")));
			SendMessage(hList, LB_SETITEMDATA, index, 30);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("�������")));
			SendMessage(hList, LB_SETITEMDATA, index, 31);
			index = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("������")));
			SendMessage(hList, LB_SETITEMDATA, index, 30);
			break;
		}

	}

	// ������� LBN_SELCHANGE ������ ���������� � ��� ������, ����� ���������� ����� ������� � ������
	if(id == IDC_MONTH && codeNotify == LBN_SELCHANGE)
	{
		// ������� ������ ���������� �������� ListBox
		int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
		// ������� ��������, ��������� � ��������� ��������� ������
		int day = SendMessage(hList, LB_GETITEMDATA, index, 0);
		TCHAR buffer[10];
		// ������ ����� � ���������� �������� ������
		SendMessage(hList, LB_GETTEXT, index, LPARAM(buffer));
		if(!lstrcmp(buffer, TEXT("�������"))) // ��������� ����� - �������?
		{
			// ���������, ���������� ��� ��� ���
			int status = SendMessage(hCheck, BM_GETCHECK, 0, 0);
			if(status == BST_CHECKED)
				day++;
		}
		wsprintf(buffer, TEXT("%d"), day);
		// ������������� ���������� ���� � EditControl
		SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(buffer));
	}
}

BOOL CALLBACK SeasonsDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}