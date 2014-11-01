#include "MyDialog.h"

// �� ��������� ��� ������� ������������ ���������� � ����������� ������ �� ����������� ����������� ����������
// ������ � ���� �� EXE ��� DLL. �� ������ �������, ����� ��������� �������� EXE ��������� ������������ ��������� ����������.
// ���������� �����, �������������� ���������� ������������� ���������� ����� ������������ EXE ��� DLL.
// ����� ����� EXE - ��� DLL - ����� ������� �� ������ ��������. �� ���������� ��� ������� ������������ ������� ����������
// � �����. ��������, ��� ���������� ��������� ���� ��� ���������� � ������.text, �� ������������������ ������ - � ��� ���.bss,
// � ������������������ � � ������.data. ����� ����������� ��������, ������������ ������������ � �������������, ����� ���������
// ���� ������� � EXE - ��� DLL - �����, ��������� ��������� �����������:
// #pragma data_seg("���_�������") 
// ���� ����� ���������� �������� � ����������� �������, ����������� ������� �� ������������ ����� ����������� ���������� EXE
// ��� DLL. �� ��������� ������ �������� �������� ���� ����� ����������. �� ����� ������������� � ��������� ������� ����������,
// ������� ������ ���� �������� ���� ��������� EXE ��� DLL; ����� ������� �� ������ ��������� ����� ���������� ���� ����������
// ��� ������ �������� EXE ��� DLL.
// ����� ���������� ����� ������������, ������ �������� ����������� �������� �� � ����� - �� ������ ����. ���� ����� ��������
// ������������, ��� ���������� � ���� ������� ������ ���� ������. ��� ����� ������������ ���� / SECTION ������������
// SECTION:���, ��������
// �� ���������� ������� ��� �������, �������� �������� �� ������ ��������.
// http://msdn.microsoft.com/en-us/library/sf9b18xk(v=vs.90).aspx

#pragma data_seg("my_shared_section")
int counter = 0;
#pragma data_seg()
#pragma comment (linker, "/SECTION:my_shared_section,RWS")

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog()
{
	ptr = this;
	++counter;
}

CMyDialog::~CMyDialog()
{
	--counter;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if (LOWORD(wp) == IDC_BUTTON1)
	{
		char str[50];
		wsprintf(str, "���������� ���������� ����������� ����������: %d", counter);
		MessageBox(hDialog, str, "����� ������", MB_OK | MB_ICONINFORMATION);
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