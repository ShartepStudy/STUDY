#include "menu_dlg.h"

CMenuBarDlg* CMenuBarDlg::ptr = NULL;

static HBITMAP paHbm;

CMenuBarDlg::CMenuBarDlg(void)
{
	ptr = this;
	bShowStatusBar = TRUE;
}

void CMenuBarDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMenuBarDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	// ���������� ���������� ����
	hEdit = GetDlgItem(hDialog, IDC_EDIT2);
	// �������� ���� �� �������� ����������
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2));
	// ������������� ���� � �������� ���� ����������
	SetMenu(hDialog, hMenu);

  paHbm = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
  SetMenuItemBitmaps(hMenu, ID_PASTE, MF_BYCOMMAND, paHbm, paHbm);

	return TRUE;
}

// ���������� ��������� WM_COMMAND ����� ������ ��� ������ ������ ����
void CMenuBarDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_UNDO:
		// ������ ��������� ��������
		SendMessage(hEdit, WM_UNDO, 0, 0); 
		break;
	case ID_CUT:
		// "���������" ����������� ��������� ������
		SendMessage(hEdit, WM_CUT, 0, 0); 
		break;
	case ID_COPY:
		// ����������� ����������� ��������� ������ � ����� ������
		SendMessage(hEdit, WM_COPY, 0, 0); 
		break;
	case ID_PASTE:
		// ������� ������ � Edit Control �� ������ ������
		SendMessage(hEdit, WM_PASTE, 0, 0); 
		break;
	case ID_DEL:
		// �������� ����������� ��������� ������
		SendMessage(hEdit, WM_CLEAR, 0, 0); 
		break;
	case ID_SELECTALL:
		// ��������� ����� ������ � Edit Control
		SendMessage(hEdit, EM_SETSEL, 0, -1); 
		break;
	}
}

// ���������� ��������� WM_SIZE ����� ������ ��� ��������� �������� �������� ����
// ���� ��� ������������/�������������� �������� ����
void CMenuBarDlg::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect1;
	// ��������� ��������� ���������� ������� �������� ����
	GetClientRect(hDialog, &rect1);
	// ��������� ����� �������� ���������� ����
	MoveWindow(hEdit, rect1.left, rect1.top, rect1.right, rect1.bottom, 1);
}

// ���������� WM_INITMENUPOPUP ����� ������ ��������������� 
// ����� ������������ ������������ ����
void CMenuBarDlg::Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu) 
{
	if(item == 0) // �������������� ����� ���� "������"
	{
		// ������� ��������� ������
		DWORD dwPosition = SendMessage(hEdit, EM_GETSEL, 0, 0); 
		WORD wBeginPosition = LOWORD(dwPosition);
		WORD wEndPosition = HIWORD(dwPosition);

		if(wEndPosition != wBeginPosition) // ����� �������?
		{
			// ���� ��,
			// �� ������������ ����� ������ ���� "����������", "��������" � "�������"
			EnableMenuItem(hMenu, ID_COPY, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, ID_CUT, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, ID_DEL, MF_BYCOMMAND | MF_ENABLED );
		}
		else
		{
			// � ���� ���,
			// �� ������ ���� "����������", "��������" � "�������" ����� ������������
			EnableMenuItem(hMenu, ID_COPY, MF_BYCOMMAND | MF_GRAYED );
			EnableMenuItem(hMenu, ID_CUT, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, ID_DEL, MF_BYCOMMAND | MF_GRAYED);
		}

		if(IsClipboardFormatAvailable(CF_TEXT)) // ������� �� ����� � ������ ������?
			// ���� ��,
			// �� ����� ���� "��������" ����� �����������
			EnableMenuItem(hMenu, ID_PASTE, MF_BYCOMMAND | MF_ENABLED);
		else 
			// ���� ���,
			// �� ����� ���� "��������" �� ����� �����������
			EnableMenuItem(hMenu, ID_PASTE, MF_BYCOMMAND | MF_GRAYED);

		// ����� ������� ������?
		if(SendMessage(hEdit, EM_CANUNDO, 0, 0)) 
			// ���� �� - "������" ���������
			// 
			EnableMenuItem(hMenu, ID_UNDO, MF_BYCOMMAND | MF_ENABLED);
		else 
			EnableMenuItem(hMenu, ID_UNDO, MF_BYCOMMAND | MF_GRAYED);

		// ����� ������ � Edit Control
		int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0); 
		// ������� ���� ����� � Edit Control?
		if(length != wEndPosition - wBeginPosition) 
			// ���� �� ����
			EnableMenuItem(hMenu, ID_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
		else 
			EnableMenuItem(hMenu, ID_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
	}
}

BOOL CALLBACK CMenuBarDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
		HANDLE_MSG(hwnd, WM_INITMENUPOPUP, ptr->Cls_OnInitMenuPopup);
	}
	return FALSE;
}