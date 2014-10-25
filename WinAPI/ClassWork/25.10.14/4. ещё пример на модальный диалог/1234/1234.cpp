#include <windows.h>
#include <vector>
#include "resource.h"
using namespace std;

//��������� �������� �������� � ����������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModal(HWND, UINT, WPARAM, LPARAM);

//������ ��� ��������� ���������� �� ������� ����
HWND hwndList, hwndStatic, hwndButton1, hwndButton2, hwndButton3;

//������ ��������� ����� ��������������� �������
HWND hwnd1, hwnd2, hwnd3, hwnd4, hwnd5;

//������������ ��� ��������� ������� � ������ 
LRESULT ind;

//����������� ��������
enum Action { DEL, ADD, EDIT } action;//������������ ��� �������� ����������������
//���������� ���� �� ������ ������� �������

//��������������� ������
wchar_t str[400];

//��������� ������ ��� �������� ������������ ����������
typedef struct
{
	wchar_t FullName[50];
	wchar_t BirthDate[50];
	wchar_t Phone[50];
	wchar_t Email[50];
	wchar_t Address[50];
}INFO;

//����������� ���������� ������� ��������
INFO info[SIZE] =
{
	{ TEXT("�������� ��������"), TEXT("7 ������� 1981"), TEXT("050 123 45 52"), TEXT("gorodnyuk_v@mail.ru"), TEXT("��.���������, �.25, ��.2") },
	{ TEXT("�������� �������"), TEXT("17 ������ 1993"), TEXT("067 524 78 25"), TEXT("fire_dima@mail.ru"), TEXT("��.��������, �.11") },
	{ TEXT("������� �������"), TEXT("4 ����� 1975"), TEXT("063 654 20 00"), TEXT("hot_alex@mail.ru"), TEXT("��.�.����������, �.14, ��.12") },
	{ TEXT("����� �����"), TEXT("8 ���� 1992"), TEXT("095 951 77 62"), TEXT("kabir_kabir@gmail.com"), TEXT("��.��.��������, �.1, ��.15") },
	{ TEXT("���� ��������"), TEXT("17 ������ 1990"), TEXT("063 542 87 72"), TEXT("nan90@yandex.ru"), TEXT("��.���������, �.17, ��.75") },
	{ TEXT("������ ��������"), TEXT("21 �������� 1995"), TEXT("067 956 32 60"), TEXT("veronika@pisem.net"), TEXT("��.�����������������, �.12-�, ��.51") },
	{ TEXT("����� ��������"), TEXT("6 ������� 1994"), TEXT("067 985 78 26"), TEXT("cat_valentin@ukr.net"), TEXT("��.������� ������������, �.3") },
	{ TEXT("��������� ��������"), TEXT("10 ������� 1986"), TEXT("063 141 65 22"), TEXT("killer_boris@yandex.ru"), TEXT("��.����������, �.2, ��.10") },
	{ TEXT("�������� �������"), TEXT("16 ����� 1987"), TEXT("067 546 12 18"), TEXT("cntgfyjd@ukr.net"), TEXT("��.����������, �.18, ��.17") },
	{ TEXT("������� ���������"), TEXT("10 ������� 1982"), TEXT("093 541 43 58"), TEXT("q1w2e3r4t5@yandex.ru"), TEXT("��.����������, �.54, ��.142") },
};

//�� ������ ������������ ������� ������ ������
vector <INFO> v(info, info + SIZE);

//������� ���������� ������� 
void fillStatic(int index)
{
	wcscpy_s(str, TEXT("�����:\n"));
	wcscat_s(str, v[index].Address);
	wcscat_s(str, TEXT("\n���� ��������:\n"));
	wcscat_s(str, v[index].BirthDate);
	wcscat_s(str, TEXT("\n�������:\n"));
	wcscat_s(str, v[index].Phone);
	wcscat_s(str, TEXT("\n����������� �����:\n"));
	wcscat_s(str, v[index].Email);
	SetWindowText(hwndStatic, str);
}

//������� �������� ��������
void delElement()
{

	if (v.size() == 0) return;

	//�������� ������ ����������� �������� ������
	ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
	//������� ������� �� ������
	SendMessage(hwndList, LB_DELETESTRING, ind, 0);
	//������� ������� �� �������
	v.erase(v.begin() + ind);
	//������� ������
	SetWindowText(hwndStatic, TEXT(""));

	if (v.size() == 0) return;

	SendMessage(hwndList, LB_SETCURSEL, 0, 0);
	fillStatic(0);
}

//������� ���������� ��������
void addElement()
{
	INFO add;
	//�������� ���������� � ����������� �������� �� �������� �����
	GetWindowText(hwnd1, add.FullName, sizeof(add.FullName));
	GetWindowText(hwnd2, add.Address, sizeof(add.Address));
	GetWindowText(hwnd3, add.BirthDate, sizeof(add.BirthDate));
	GetWindowText(hwnd4, add.Phone, sizeof(add.Phone));
	GetWindowText(hwnd5, add.Email, sizeof(add.Email));

	//��������� � � ������
	SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)add.FullName);
	//� � ������
	v.push_back(add);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//������ ������� ����
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	w.lpszClassName = TEXT("������ ������������� ���������� �������");
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);

	//������������ ����� ����
	RegisterClass(&w);

	//�������� �������� ����
	hwnd = CreateWindow(TEXT("������ ������������� ���������� �������"), TEXT("������ ������������� ���������� �������"), WS_OVERLAPPEDWINDOW, 100, 100, 470, 250, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//������� �������� ���������� �� ������� ����
	hwndList = CreateWindow(TEXT("LISTBOX"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY, 10, 10, 180, 150, hwnd, (HMENU)ID_LIST1, hInstance, NULL);
	hwndStatic = CreateWindow(TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 215, 10, 230, 147, hwnd, (HMENU)ID_STATIC1, hInstance, NULL);
	hwndButton1 = CreateWindow(TEXT("BUTTON"), TEXT("�������"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 180, 140, 25, hwnd, (HMENU)ID_BUTTON1, hInstance, NULL);
	hwndButton2 = CreateWindow(TEXT("BUTTON"), TEXT("��������"), WS_VISIBLE | WS_CHILD | WS_BORDER, 158, 180, 140, 25, hwnd, (HMENU)ID_BUTTON2, hInstance, NULL);
	hwndButton3 = CreateWindow(TEXT("BUTTON"), TEXT("�������������"), WS_VISIBLE | WS_CHILD | WS_BORDER, 306, 180, 140, 25, hwnd, (HMENU)ID_BUTTON3, hInstance, NULL);

	//�������� ������ �� �������
	for (int i = 0; i < SIZE; i++)
		SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)v[i].FullName);

	SendMessage(hwndList, LB_SETCURSEL, 0, 0);
	fillStatic(0);

	//��������� ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.wParam;
}


//��������� �������� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	static HINSTANCE hInstance;

	switch (Message)
	{

	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lparam)->hInstance;
		break;

	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
			//������������ ����� �� ������ ��� �������� �������
		case ID_BUTTON1:
			action = DEL;
			if (ind != LB_ERR && !v.empty())//���� ������������ ������� ������� ������
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);
			else
				MessageBox(hwnd, TEXT("��� �������� ���������� ������� ������� � ������"),
				TEXT("�������� ������� � ������"), MB_OK);
			break;

			//������������ ����� �� ������ ��� ���������� �������	
		case ID_BUTTON2:
			action = ADD;
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);//������ ���������� ���� 			
			break;

			//������������ ����� �� ������ ��� ���������� �������	
		case ID_BUTTON3:
			action = EDIT;
			if (ind != LB_ERR && !v.empty())
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);//������ ���������� ���� 
			else
				MessageBox(hwnd, TEXT("��� �������������� ���������� ������� ������� � ������"), TEXT("�������� ������� � ������"), MB_OK);
			break;

			//������������ ������� ������� ������
		case ID_LIST1:
			//�������� ������ ����������� �������� ������
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (ind != LB_ERR)
				//��������� ������
				fillStatic((int)ind);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}

//���������� ��������� ���������� ����
BOOL CALLBACK DlgProcModal(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//�������� ������ ��������� ����� ��������������� �������
	hwnd1 = GetDlgItem(hDlg, IDC_EDIT1);
	hwnd2 = GetDlgItem(hDlg, IDC_EDIT2);
	hwnd3 = GetDlgItem(hDlg, IDC_EDIT3);
	hwnd4 = GetDlgItem(hDlg, IDC_EDIT4);
	hwnd5 = GetDlgItem(hDlg, IDC_EDIT5);

	switch (iMsg)
	{
		//������������� ��������������� �������
	case WM_INITDIALOG:
		if (action == DEL)//���� ��������
		{
			//�������� �� ���� ����� �� ��������� �������	
			SetWindowText(hDlg, TEXT("��������"));
			//�������� ������ ����������� �������� ������
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			//��������� �������� ���� ��������� �����������
			SetWindowText(hwnd1, v[ind].FullName);
			SetWindowText(hwnd2, v[ind].Address);
			SetWindowText(hwnd3, v[ind].BirthDate);
			SetWindowText(hwnd4, v[ind].Phone);
			SetWindowText(hwnd5, v[ind].Email);

		}
		else if (action == ADD)//���� ����������
		{
			//�������� �� ���� ����� �� ��������� �������	
			SetWindowText(hDlg, TEXT("����������"));
			for (int i = IDC_EDIT1; i <= IDC_EDIT5; i++)//� �����
			{
				HWND hwnd = GetDlgItem(hDlg, i);//�������� ������ �������� �����
				SendMessage(hwnd, EM_SETREADONLY, FALSE, 0);//������ �� ���������� ��� ��������������
			}
		}
		else if (action == EDIT)//���� ��������������
		{
			//�������� �� ���� ����� �� ��������� �������	
			SetWindowText(hDlg, TEXT("��������������"));

			for (int i = IDC_EDIT1; i <= IDC_EDIT5; i++)//� �����
			{
				HWND hwnd = GetDlgItem(hDlg, i);//�������� ������ �������� �����
				SendMessage(hwnd, EM_SETREADONLY, FALSE, 0);//������ �� ���������� ��� ��������������
			}
			//�������� ������ ����������� �������� ������
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			//��������� ��������� ���� ��������������� �����������
			SetWindowText(hwnd1, v[ind].FullName);
			SetWindowText(hwnd2, v[ind].Address);
			SetWindowText(hwnd3, v[ind].BirthDate);
			SetWindowText(hwnd4, v[ind].Phone);
			SetWindowText(hwnd5, v[ind].Email);
		}

		return TRUE;
	case WM_CLOSE:
		//��������� ����
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK://���� ������ ������ OK
			if (action == DEL)//� ���� ������� ��������
				delElement();//�������	

			else if (action == ADD)//���� ������� ����������
				addElement();//���������

			else if (action == EDIT)//���� ������� ��������������
			{
				//������ �������� ������� ��������
				delElement();//�������	

				//� ���������� ������
				addElement();
			}
			EndDialog(hDlg, 0);	//��������� ������
			break;

		case IDCANCEL:	//���� ������ ������ CANCEL ��������� ������					
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
