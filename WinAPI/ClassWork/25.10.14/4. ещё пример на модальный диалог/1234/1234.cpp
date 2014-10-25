#include <windows.h>
#include <vector>
#include "resource.h"
using namespace std;

//прототипы процедур главного и диалогового окна
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModal(HWND, UINT, WPARAM, LPARAM);

//хэндлы для элементов управления на главном окне
HWND hwndList, hwndStatic, hwndButton1, hwndButton2, hwndButton3;

//хэндлы текстовых полей дополнительного диалога
HWND hwnd1, hwnd2, hwnd3, hwnd4, hwnd5;

//используется для получения индекса в списке 
LRESULT ind;

//выполняемые действия
enum Action { DEL, ADD, EDIT } action;//используется при создании соответствующего
//модального окна на основе единого шаблона

//вспомогательная строка
wchar_t str[400];

//структура данных для хранения персональной информации
typedef struct
{
	wchar_t FullName[50];
	wchar_t BirthDate[50];
	wchar_t Phone[50];
	wchar_t Email[50];
	wchar_t Address[50];
}INFO;

//изначальное заполнение массива структур
INFO info[SIZE] =
{
	{ TEXT("Городнюк Владимир"), TEXT("7 февраля 1981"), TEXT("050 123 45 52"), TEXT("gorodnyuk_v@mail.ru"), TEXT("ул.Успенская, д.25, кв.2") },
	{ TEXT("Горяйнов Дмитрий"), TEXT("17 января 1993"), TEXT("067 524 78 25"), TEXT("fire_dima@mail.ru"), TEXT("ул.Степовая, д.11") },
	{ TEXT("Горячев Алексей"), TEXT("4 марта 1975"), TEXT("063 654 20 00"), TEXT("hot_alex@mail.ru"), TEXT("ул.Б.Арнаутская, д.14, кв.12") },
	{ TEXT("Гулам Кабир"), TEXT("8 июля 1992"), TEXT("095 951 77 62"), TEXT("kabir_kabir@gmail.com"), TEXT("ул.Ал.Невского, д.1, кв.15") },
	{ TEXT("Джан Нангялай"), TEXT("17 апреля 1990"), TEXT("063 542 87 72"), TEXT("nan90@yandex.ru"), TEXT("ул.Еврейская, д.17, кв.75") },
	{ TEXT("Жукова Вероника"), TEXT("21 сентября 1995"), TEXT("067 956 32 60"), TEXT("veronika@pisem.net"), TEXT("ул.Пантелеймоновская, д.12-а, кв.51") },
	{ TEXT("Котов Валентин"), TEXT("6 декабря 1994"), TEXT("067 985 78 26"), TEXT("cat_valentin@ukr.net"), TEXT("ул.Богдана Хмельницкого, д.3") },
	{ TEXT("Приходько Геннадий"), TEXT("10 августа 1986"), TEXT("063 141 65 22"), TEXT("killer_boris@yandex.ru"), TEXT("ул.Дальницкая, д.2, кв.10") },
	{ TEXT("Степанов Георгий"), TEXT("16 марта 1987"), TEXT("067 546 12 18"), TEXT("cntgfyjd@ukr.net"), TEXT("ул.Мельницкая, д.18, кв.17") },
	{ TEXT("Федотов Александр"), TEXT("10 февраля 1982"), TEXT("093 541 43 58"), TEXT("q1w2e3r4t5@yandex.ru"), TEXT("ул.Затонского, д.54, кв.142") },
};

//на основе статического массива создаём вектор
vector <INFO> v(info, info + SIZE);

//функция заполнения статика 
void fillStatic(int index)
{
	wcscpy_s(str, TEXT("Адрес:\n"));
	wcscat_s(str, v[index].Address);
	wcscat_s(str, TEXT("\nДата рождения:\n"));
	wcscat_s(str, v[index].BirthDate);
	wcscat_s(str, TEXT("\nТелефон:\n"));
	wcscat_s(str, v[index].Phone);
	wcscat_s(str, TEXT("\nЭлектронный адрес:\n"));
	wcscat_s(str, v[index].Email);
	SetWindowText(hwndStatic, str);
}

//функция удаления элемента
void delElement()
{

	if (v.size() == 0) return;

	//получаем индекс выделенного элемента списка
	ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
	//удаляем элемент из списка
	SendMessage(hwndList, LB_DELETESTRING, ind, 0);
	//удаляем элемент из вектора
	v.erase(v.begin() + ind);
	//очищаем статик
	SetWindowText(hwndStatic, TEXT(""));

	if (v.size() == 0) return;

	SendMessage(hwndList, LB_SETCURSEL, 0, 0);
	fillStatic(0);
}

//функция добавления элемента
void addElement()
{
	INFO add;
	//получаем информацию о добавляемом элементе из тестовых полей
	GetWindowText(hwnd1, add.FullName, sizeof(add.FullName));
	GetWindowText(hwnd2, add.Address, sizeof(add.Address));
	GetWindowText(hwnd3, add.BirthDate, sizeof(add.BirthDate));
	GetWindowText(hwnd4, add.Phone, sizeof(add.Phone));
	GetWindowText(hwnd5, add.Email, sizeof(add.Email));

	//добавляем её в список
	SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)add.FullName);
	//и в вектор
	v.push_back(add);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//создаём главное окно
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	w.lpszClassName = TEXT("Пример использования модального диалога");
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);

	//регистрируем класс окна
	RegisterClass(&w);

	//создание главного окна
	hwnd = CreateWindow(TEXT("Пример использования модального диалога"), TEXT("Пример использования модального диалога"), WS_OVERLAPPEDWINDOW, 100, 100, 470, 250, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//добавим элементы управления на главное окно
	hwndList = CreateWindow(TEXT("LISTBOX"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY, 10, 10, 180, 150, hwnd, (HMENU)ID_LIST1, hInstance, NULL);
	hwndStatic = CreateWindow(TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 215, 10, 230, 147, hwnd, (HMENU)ID_STATIC1, hInstance, NULL);
	hwndButton1 = CreateWindow(TEXT("BUTTON"), TEXT("Удалить"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 180, 140, 25, hwnd, (HMENU)ID_BUTTON1, hInstance, NULL);
	hwndButton2 = CreateWindow(TEXT("BUTTON"), TEXT("Добавить"), WS_VISIBLE | WS_CHILD | WS_BORDER, 158, 180, 140, 25, hwnd, (HMENU)ID_BUTTON2, hInstance, NULL);
	hwndButton3 = CreateWindow(TEXT("BUTTON"), TEXT("Редактировать"), WS_VISIBLE | WS_CHILD | WS_BORDER, 306, 180, 140, 25, hwnd, (HMENU)ID_BUTTON3, hInstance, NULL);

	//заполним список из вектора
	for (int i = 0; i < SIZE; i++)
		SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)v[i].FullName);

	SendMessage(hwndList, LB_SETCURSEL, 0, 0);
	fillStatic(0);

	//запускаем цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.wParam;
}


//процедура главного окна
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
			//пользователь нажал на кнопку для удаления записей
		case ID_BUTTON1:
			action = DEL;
			if (ind != LB_ERR && !v.empty())//если пользователь выделил элемент списка
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);
			else
				MessageBox(hwnd, TEXT("Для удаления необходимо выбрать элемент в списке"),
				TEXT("Выделите элемент в списке"), MB_OK);
			break;

			//пользователь нажал на кнопку для добавления записей	
		case ID_BUTTON2:
			action = ADD;
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);//создаём диалоговое окно 			
			break;

			//пользователь нажал на кнопку для добавления записей	
		case ID_BUTTON3:
			action = EDIT;
			if (ind != LB_ERR && !v.empty())
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
				hwnd, DlgProcModal);//создаём диалоговое окно 
			else
				MessageBox(hwnd, TEXT("Для редактирования необходимо выбрать элемент в списке"), TEXT("Выделите элемент в списке"), MB_OK);
			break;

			//пользователь выделил элемент списка
		case ID_LIST1:
			//получаем индекс выделенного элемента списка
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			if (ind != LB_ERR)
				//заполняем статик
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

//диалоговая процедура модального окна
BOOL CALLBACK DlgProcModal(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	//получаем хэндлы текстовых полей дополнительного диалога
	hwnd1 = GetDlgItem(hDlg, IDC_EDIT1);
	hwnd2 = GetDlgItem(hDlg, IDC_EDIT2);
	hwnd3 = GetDlgItem(hDlg, IDC_EDIT3);
	hwnd4 = GetDlgItem(hDlg, IDC_EDIT4);
	hwnd5 = GetDlgItem(hDlg, IDC_EDIT5);

	switch (iMsg)
	{
		//инициализация дополнительного диалога
	case WM_INITDIALOG:
		if (action == DEL)//если удаление
		{
			//помещаем об этом текст на заголовке диалога	
			SetWindowText(hDlg, TEXT("Удаление"));
			//получаем индекс выделенного элемента списка
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			//заполняем тестовые поля удаляемой информацией
			SetWindowText(hwnd1, v[ind].FullName);
			SetWindowText(hwnd2, v[ind].Address);
			SetWindowText(hwnd3, v[ind].BirthDate);
			SetWindowText(hwnd4, v[ind].Phone);
			SetWindowText(hwnd5, v[ind].Email);

		}
		else if (action == ADD)//если добавление
		{
			//помещаем об этом текст на заголовке диалога	
			SetWindowText(hDlg, TEXT("Добавление"));
			for (int i = IDC_EDIT1; i <= IDC_EDIT5; i++)//в цикле
			{
				HWND hwnd = GetDlgItem(hDlg, i);//получаем хэндлы тестовых полей
				SendMessage(hwnd, EM_SETREADONLY, FALSE, 0);//делаем их доступными для редактирования
			}
		}
		else if (action == EDIT)//если редактирование
		{
			//помещаем об этом текст на заголовке диалога	
			SetWindowText(hDlg, TEXT("Редактирование"));

			for (int i = IDC_EDIT1; i <= IDC_EDIT5; i++)//в цикле
			{
				HWND hwnd = GetDlgItem(hDlg, i);//получаем хэндлы тестовых полей
				SendMessage(hwnd, EM_SETREADONLY, FALSE, 0);//делаем их доступными для редактирования
			}
			//получаем индекс выделенного элемента списка
			ind = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			//заполняем текстовые поля соответствующей информацией
			SetWindowText(hwnd1, v[ind].FullName);
			SetWindowText(hwnd2, v[ind].Address);
			SetWindowText(hwnd3, v[ind].BirthDate);
			SetWindowText(hwnd4, v[ind].Phone);
			SetWindowText(hwnd5, v[ind].Email);
		}

		return TRUE;
	case WM_CLOSE:
		//закрываем окно
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK://если нажата кнопка OK
			if (action == DEL)//и было выбрано удаление
				delElement();//удаляем	

			else if (action == ADD)//было выбрано добавление
				addElement();//добавляем

			else if (action == EDIT)//было выбрано редактирование
			{
				//делаем удаление старого элемента
				delElement();//удаляем	

				//и добавление нового
				addElement();
			}
			EndDialog(hDlg, 0);	//закрываем диалог
			break;

		case IDCANCEL:	//если нажата кнонка CANCEL закрываем диалог					
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
