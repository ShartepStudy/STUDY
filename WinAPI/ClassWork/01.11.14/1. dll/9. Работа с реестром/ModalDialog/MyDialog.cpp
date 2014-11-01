#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog()
{
	ptr = this;
	pathes.clear();
}

CMyDialog::~CMyDialog()
{
	for (int i = 0; i < pathes.size(); i++)
		delete[]pathes[i];
	pathes.clear();
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	LoadData();
}

void CMyDialog::OnOpenDialog()
{
	HMENU hMain = GetMenu(hDialog);
	HMENU hSubMenu = GetSubMenu(hMain, 0);

	if (pathes.size() == 0)
		DeleteMenu(hSubMenu, 0, MF_BYPOSITION);

	char *PathName = new char[MAX_PATH];
	ZeroMemory(PathName, MAX_PATH);
	char FileTitle[MAX_PATH];

	OPENFILENAME open = { sizeof(OPENFILENAME) };
	open.hwndOwner = hDialog;
	open.lpstrFilter = "Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0";
	open.lpstrFile = PathName;
	open.nMaxFile = MAX_PATH;
	open.lpstrFileTitle = FileTitle;
	open.nMaxFileTitle = MAX_PATH;
	open.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	open.lpstrDefExt = "txt";

	if (GetOpenFileName(&open))
	{
		string str = "�� ������� ��� �������� ����:\n";
		str += PathName;
		MessageBox(hDialog, str.c_str(), "������ �������", MB_OK);
		for (int j = 0; j < pathes.size(); j++)
		{
			if (!strcmp(pathes[j], PathName))
			{
				delete[]PathName;
				return;
			}
		}
		AppendMenu(hSubMenu, MF_STRING, WM_USER + pathes.size(), FileTitle);
		pathes.push_back(PathName);
	}
	else
		delete[]PathName;

}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_COMMAND:
		if (LOWORD(wp) == IDC_BUTTON1)
			ptr->OnOpenDialog();
		break;
	case WM_CLOSE:
		ptr->OnClose();
		break;
	case WM_INITDIALOG:
		ptr->OnInitDialog(hWnd);
		break;
	}
	return 0;
}

void CMyDialog::OnClose()
{
	SaveData();
	EndDialog(hDialog, 0);
}

void CMyDialog::SaveData()
{
	HKEY key;
	LONG Result;
	Result = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\���-1321\\Registry", 0, 0, 0, KEY_ALL_ACCESS, 0, &key, 0);
	if (Result != ERROR_SUCCESS)
		return;

	char Name[10];
	DWORD size = pathes.size();

	if (size != 0)
	{
		RegSetValueEx(key, "Quantity", 0, REG_DWORD, (const BYTE*)&size, sizeof(size));
		for (int i = 0; i < size; i++)
		{
			wsprintf(Name, "Path%d", i);
			Result = RegSetValueEx(key, Name, 0, REG_SZ, (const BYTE*)pathes[i], strlen(pathes[i]) + 1);
		}
	}
	RegCloseKey(key);
}

void CMyDialog::LoadData()
{
	/*
	�������� ����� ������������ ������� ��� ������ � ��������:
	RegCreateKeyEx    �������� ������ ����� (�������);
	RegOpenKeyEx    �������� ������������� �����;
	RegCloseKey    �������� �����;
	RegSetValueEx    ��������� �������� ���������;
	RegQueryValueEx    ������ �������� ���������;
	RegEnumKeyEx    �������� ������ ��������� (�����������) ������� �����;
	RegEnumValue    �������� ������ ���������� ������� �����;
	RegDeleteKey    ������� ����;
	RegDeleteValue    ������� ��������.
	���� ���� ��� �������� ����� � ��� �� �������, �� ������������ ����� "Ex"-���������
	*/

	/*
	������� ������� ������ �������.
	���� ������ ��� ����������, ������� ��������� ���.
	����� �������� �� ������������� � ��������.

	RegCreateKeyEx(
	1) HKEY hKey,
	2) LPCTSTR lpSubKey,
	3) DWORD Reserved,
	4) LPTSTR lpClass,
	5) DWORD dwOptions,
	6) REGSAM samDesired,
	7) LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	8) PHKEY phkResult,
	9) LPDWORD lpdwDisposition)

	1) hKey ��������� ������������ �������.
	2) lpSubKey ��������� �� ������, ������������� ������� ������, ������� �������� ��� ������������ ��� ������������ �������.
	3) Reserved ��������������� - 0.
	4) lpClass ��������� �� ������, ������������� ������� ������, ������� �������� ����� ����� �������. ����� ���� �������������� � ����� NULL. ������������ ��� ����������� � ���������� �������.
	5) dwOptions �������� ����� ��������� ��������� ��������.
	REG_OPTION_BACKUP_RESTORE ���� ���� ����������, ������� ���������� �������� samDesired � �������� ������� ������ � �������, ��� ���������� ����������� � �������������� �������. ���� ����� �������� �������, ������� ����������� SE_BACKUP_NAME, �� ������ ����������� � ������� ������� ACCESS_SYSTEM_SECURITY � KEY_READ. ���� ���������� ����� �������� ����������� SE_RESTORE_NAME, �� ������ ����������� � ������� ������� ACCESS_SYSTEM_SECURITY � KEY_WRITE. ���� ����� �������� ������ ������������, �� ������ ����������� � ���������������� ������� �������.
	REG_OPTION_VOLATILE ������, ��������� � ������� ����� ����� - ��������. ��� ���� ���������� ����������� � ������ � �� �����������, ����� ��������������� ���� �����������. ��� HKEY_LOCAL_MACHINE, ��� ����������, ����� ��������� ����������� ��� ���������������. ��� �������� �������, ����������� �������� RegLoadKey, ��� ����������, ����� ��������� ������� RegUnLoadKey. ������� RegSaveKey �� ��������� ���������� ������� �������. ���� ���� ������������, ���� ������ ��� ����������.
	REG_OPTION_NON_VOLATILE ������, ��������� � ������� ����� ����� - �� ��������. ��� ���� ���������� ������������ � ���� �������. ������� RegSaveKey ��������� �� ���������� �������.

	6) samDesired ���������� ����� ������� ��� ������������ �������.
	7) lpSecurityAttributes ��������� �� ��������� SECURITY_ATTRIBUTES. ���� �������� ����� NULL, �� ��������� ������� �� ����������� ����������� (��������) ���������. � ��� ���������, ������ ���������� ������ �������. ���� �������� ����� NULL, ������ �������� ���������� ������ �� ���������. ������ ���������� �������� (ACL) � �������� �� ��������� ����������� ������ ��� �������, ����������� �� ������������� �������.
	8) phkResult ��������� �� ����������, ���������� ��������� ��������� ��� ���������� �������.
	9) lpdwDisposition ��������� �� ����������, � ������� ������������ ���� �� ��������� ��������.

	REG_CREATED_NEW_KEY ������ �� ���������� � ����� ������
	REG_OPENED_EXISTING_KEY ������ ����������


	���� �������� ��������� �������, ������� ������ ERROR_SUCCESS, � ��������� ������ ������ ��������� ��� ������, ������������ � Winerror.h

	����� ��������� ��������� ������� ������� � ��� ����������� ������ ��������, �������� ��������� ��� ���������� �������� ����������. ����� ����������� �������� ��������� ������� ������� ������ ���� ��������� ������. ��� ����� ���������� ������� RegCloseKey, �������� ������� ������� ����.
	*/

	/*
	������� ���������� ���������� � ��������� ������� � �������� ����� ���������.

	LONG RegQueryValueEx(
	1) HKEY hKey,
	2) LPCTSTR lpValueName,
	3) LPDWORD lpReserved,
	4) LPDWORD lpType,
	5) LPBYTE lpData,
	6) LPDWORD lpcbData)

	1) hKey ��������� ��������� �������. ������ ������ ���� ������ � ������� KEY_QUERY_VALUE.
	2) lpValueName ��������� �� �-������, ���������� �������� ���������, � ������� ���������� ����������. ���� �������� - NULL ��� ������ ������, �� ������������ ���������� � ��������� �� ���������.
	3) lpReserved �������������� - NULL.
	4) lpType ��������� �� ����������, ������� �������� ��� ������, ����������� � ���������. ���� ����� NULL, �� ��������������, ���������� �� ������������.
	5) lpData ��������� �� ������, ���������� ������ ���������. ���� �������� - NULL, �� ������ �� ������������. ���� ������ - ��� ������, �� ������� ��������� ������� �������� �������.
	6) lpcbData ��������� �� ����������, ������� ���������� ������ ������, ������������ ������ �� ���������, � ������. ����� ����, ��� ������� ������ ��������, ��� ���������� ����� ��������� ������ ������, ������������� � �����. ���� ������ ����� ��������� �������� (REG_xxx_SZ), �� ����� ���������� � ������� ������ (������� ������� ��� REG_MULTI_SZ). ���� ������ ������, ������������ ��� ���������� ������, �� ������� ������ ERROR_MORE_DATA � �������� ��������� ������ ������ � ����������, �� ������� ��������� ���� ��������. ���� lpData - NULL, � �������� lpcbData �� �������, ������� ���������� ERROR_SUCCESS � ��������� ������ ������ � ����������, �� ������� ��������� lpcbData.

	���� ������� ��������� �������, ������������ ERROR_SUCCESS, � ��������� ������ ������������ ��������� ��� ������, ������������ � Winerror.h
	��� �����, ������� RegQueryValueEx ������������� ����������� ������������ ������� ���������, ����� ������ ������ � ���������, � ����� ��� ��� �������. ��� ��������� �������� ������ �����������, �� ���� ���������� ���������.

	*/

	/*
	������� ������������� �������� ���������.

	LONG RegSetValueEx(
	1)HKEY hKey,
	2) LPCTSTR lpValueName,
	3) DWORD Reserved,
	4) DWORD dwType,
	5) const BYTE* lpData,
	6) DWORD cbData)


	1) hKey ��������� ��������� �������. ������ ������ ���� ������ � ������� KEY_SET_VALUE.
	2) lpValueName ��������� �� ������, ������� �������� �������� ���������, �������� �������� ����� ����������. ���� ��������� � ����� ������ �� ����������, ������� ������� ���. ���� �������� ����� NULL, ��� ������ ������, �� ��������������� �������� ��������� �� ���������. � Windows Me/98/95 ������ ������ ����� �������� �� ���������, ������� ������������� �� �������� ������. � Windows 95 �� ��������� ��� ����� ��������� - REG_SZ.
	3) Reserved ��������������� - NULL.
	4) dwType ��� ������ ���������.
	5) lpData ��������� �� �����, ���������� ������, ������� ������ ���� ��������� � ��������������� ���������. ��� �����, ����� ��� REG_SZ, ������ ������ ������������� ������� ��������. ��� ���� REG_MULTI_SZ ������ ������ ������������� ����� �������� ���������.
	6) cbData ������ ������ lpData, � ������. ���� ������ ����� ��� REG_SZ, REG_MULTI_SZ ��� REG_EXPAND_SZ, �� �������� ������ ��������� ������� ��� ������� �������.

	���� ������� ��������� �������, ������������ ERROR_SUCCESS, � ��������� ������ ������������ ��������� ��� ������, ������������ � Winerror.h
	*/


	/*
	������� ��������� ���������� ����� ������

	LONG RegCloseKey(
	1) HKEY hKey)

	1) hKey ��������� ��������� �������, ������� �������� ��������.
	���� ��������� ������� ����������, ������� ���������� ERROR_SUCCESS, � ��������� ������ ������ ��������� ��� ������, ������������ � Winerror.h
	*/

	HMENU subFileMenu = CreatePopupMenu();
	HKEY key;
	LONG Result;
	Result = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\���-1321\\Registry", 0, 0, 0, KEY_ALL_ACCESS, 0, &key, 0);
	if (Result != ERROR_SUCCESS)
	{
		AppendMenu(subFileMenu, MF_STRING | MF_GRAYED, WM_USER, "(�����)");
	}
	else
	{
		DWORD len = MAX_PATH, len2 = sizeof(DWORD);
		char Name[10];
		DWORD size;
		Result = RegQueryValueEx(key, "Quantity", 0, 0, (BYTE*)&size, &len2);
		if (Result != ERROR_SUCCESS)
			AppendMenu(subFileMenu, MF_STRING | MF_GRAYED, WM_USER, "(�����)");
		else
		{
			for (int i = 0; i < size; i++)
			{
				char *PathName = new char[MAX_PATH];
				ZeroMemory(PathName, MAX_PATH);
				wsprintf(Name, "Path%d", i);
				Result = RegQueryValueEx(key, Name, 0, 0, (BYTE*)PathName, &len);
				if (Result == ERROR_SUCCESS)
				{
					if (!_access(PathName, 0))
					{
						pathes.push_back(PathName);
						char *p = strrchr(PathName, '\\');
						AppendMenu(subFileMenu, MF_STRING, WM_USER + i, p + 1);
					}

				}
				len = MAX_PATH;
			}
		}
	}
	HMENU mainMenu = CreateMenu();
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subFileMenu, "Recent Files");
	SetMenu(hDialog, mainMenu);
	RegCloseKey(key);
}