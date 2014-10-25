
#include "stdafx.h"
#include "ModlessDialog.h"

#define MAX_LOADSTRING 100

// наши сообщения
enum OurMessages 
{
	// Со значения WM_USER ( 0x0400) начинается диапазон значений, 
	// которые могут использоваться как идентификаторы
	// создаваемых программистом  сообщений.
	// Диапазон заканчивается идентификатором сообщения
	// со значением 0x7FFF 
	UM_CHANGE = WM_USER
}; 

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int		rgb[3];			// интенсивность для R-, G-, В-компонентов цвета 
HWND	hModelessDlg;	// дескриптор диалога выбора цвета
HRGN	hWndRgn;		// дескриптор региона главного окна изменения цвета
HRGN	hDlgRgn;		// дескриптор региона диалога изменения цвета

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// прототип диалоговой процедуры
INT_PTR CALLBACK	ModelessDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MODLESSDIALOG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MODLESSDIALOG));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Чтобы сообщения диалога были обработаны, необходимо вызвать функцию
		// IsDialogMessage, передав ей дескриптор диалога и адрес структуры, 
		// хранящей информацию о поступившем событии.
		// Если функция IsDialogMessage вернула не нулевое значение, 
		// то сообщение обработано диалогом и передаваться функциям 
		// TranslateMessage, DispatchMessage оно не должно.
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) && 
			!IsDialogMessage(hModelessDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, 0);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MODLESSDIALOG);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{
		// Инициализация приложения
	case WM_CREATE:
		// Создаем далоговое окно изменения цвета
		hModelessDlg = CreateDialog(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDD_MODELESS), hWnd, (DLGPROC)ModelessDlgProc); 

		// Создаем регионы (используются при перерисовке окна 
		// вследствие изменения цвета фона главного окна, см. UM_CHANGE)
		hWndRgn = CreateRectRgn(0,0,0,0);
		hDlgRgn = CreateRectRgn(0,0,0,0);
		// Приводим начальный цвет фона окна в соответствие 
		// с начальными значениями цветовых составляющих
		// (массив rgb).
		// Начальные значения нулевые, т.к. этот массив глобальный.
		// Чтобы выполнить описанное - посылаем из обработчика WM_CREATE
		// сообщение UM_CHANGE этому же окну.
		SendMessage(hWnd, UM_CHANGE, 0, 0);
		// Посылаем этому же окну сообщение ID_DIALOG_SHOW - 
		// отображение окна диалога выбора цвета и отметка 
		// соответствующего пункта в меню.
		SendMessage(hWnd, WM_COMMAND, ID_DIALOG_SHOW, 0);
		break;
		// UM_CHANGE - идентификатор сообщения, созданный нами.
		// Сообщение предназначено специально для взаимодействия
		// с диалоговым окном  изменения цвета, но может 
		// использоваться (и используется) самим главным окном.
		// 
		// Принцип взаимодействия главного окна и (немодального)
		// диалога: когда нужно передать информацию, посылаем адресату
		// сообщение.
		// 
		// Получив сообщение, адресат выполняет необходимые действия
		// (считывает/записывает данные, обновляет интерфейс и т.д.)
		// 
		// Обработчик сообщения UM_CHANGE считывает значения
		// цветовых составляющих из массива rgb и обновляет 
		// цвет фона главного окна в соответствии с этими значениями
	case UM_CHANGE:
		// получаем прямоугольник, описывающий
		// клиентскую часть главного окна
		GetClientRect(hWnd, &rect);
		// создаем прямоугольный регион 
		// по полученному только что прямоугольнику
		hWndRgn = CreateRectRgnIndirect(&rect);
		// получаем экранные координаты диалога выбора цвета
		GetWindowRect(hModelessDlg, &rect);
		// пересчитываем координаты к координатной системе главного окна
		MapWindowPoints(0, hWnd, (POINT*)&rect, 2);

		// Создаем регион, соответствующий окну диалога.
		hDlgRgn = CreateRectRgnIndirect(&rect);
		// Вырезаем из региона главного окна регион диалога
		CombineRgn(hWndRgn, hWndRgn, hDlgRgn, RGN_DIFF);
		//  В hWndRgn получился регион следующего вида:
		//	+-----------------+
		//  |   +----+        |   
		//  |   |    |        |
		//  |   |    |        |
		//  |   +----+        |
		//  +-----------------+

		// Меняем изменяем цвет его кисти окна, для чего используем
		// изменение класса окна
		SetClassLong(hWnd, GCL_HBRBACKGROUND, 
			(LONG)CreateSolidBrush(RGB(rgb[0], rgb[1], rgb[2]))); 
		// Перерисовываем фон главного окна
		// Операции с регионами здесь потребовались чтобы устранить 
		// мерцание диалога при изменении цвета главного окна
		// (из области перерисовывки исключена область,
		// занимаемая диалогом).
		InvalidateRgn(hWnd, hWndRgn, TRUE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			// Извещение ID_DIALOG_SHOW генерируется пунктом меню Dialog -> Show
		case ID_DIALOG_SHOW:
			// Отображаем окно диалога
			ShowWindow(hModelessDlg, SW_SHOW);
			// Отмечаем выбранный пункт меню
			CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), ID_DIALOG_SHOW,
				ID_DIALOG_HIDE, ID_DIALOG_SHOW, MF_BYCOMMAND);
			break;			
			// Извещение ID_DIALOG_HIDE генерируется пунктом меню Dialog -> Hide
		case ID_DIALOG_HIDE:
			// скрыть окно диалога
			ShowWindow(hModelessDlg, SW_HIDE);
			// отметить выбранный пункт меню
			CheckMenuRadioItem(GetSubMenu(GetMenu(hWnd), 1), ID_DIALOG_SHOW, 
				ID_DIALOG_HIDE, ID_DIALOG_HIDE, MF_BYCOMMAND);
			break;	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		// Удаляем регионы
		DeleteObject(hWndRgn);
		DeleteObject(hDlgRgn);
		DestroyWindow(hModelessDlg); 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Процедура обработки сообщений для диалогового окна
INT_PTR CALLBACK ModelessDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Получаем дескрипторы полос прокрутки
	HWND hRed	 = GetDlgItem(hDlg, IDC_RED); 
	HWND hGreen  = GetDlgItem(hDlg, IDC_GREEN); 
	HWND hBlue	 = GetDlgItem(hDlg, IDC_BLUE); 
	// Дескриптор активной полосы прокрутки, см. WM_VSCROLL
	HWND hCtrl; 
	// Индекс изменяемого цвета:
	// 0 - меняется красный;
	// 1 - зеленый;
	// 2 - синий
	int  index;

	switch (message)
	{
		// Инициализация диалога
	case WM_INITDIALOG:
		// Задаем диапазон скроллинга (0 - 255) для каждой из полос прокрутки
		SetScrollRange(hRed, SB_CTL, 0, 255, FALSE); 
		SetScrollRange(hGreen, SB_CTL, 0, 255, FALSE); 
		SetScrollRange(hBlue, SB_CTL, 0, 255, FALSE); 
		break;
	case WM_COMMAND:
		// При поступлении извещений IDOK и IDCANCEL
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			// Отправляем сообщение ID_DIALOG_HIDE главному окну
			// Обработчик ID_DIALOG_HIDE спрячет диалог
			// и отметит пункт меню Dialog -> Hide
			SendMessage(GetParent(hDlg), WM_COMMAND, ID_DIALOG_HIDE, 0);
			return (INT_PTR)TRUE;
		}
		break;
		// Обработка сообщений от полос прокрутки
	case WM_VSCROLL: 
		// Извлекаем из lParam дескриптор полосы прокрутки,
		// отправившей сообщение
		hCtrl = (HWND)lParam; 
		// Идентификаторы IDC_RED, IDC_GREEN, IDC_BLUE 
		// в ресурсном файле упорядочены по возрастанию,
		// при этом значение последующего идентификатора
		// на единицу превышает значение предыдущего.
		// Это позволяет по идентификатору полосы прокрутки
		// получить номер меняемого цвета:
		// index = идентификатор_полосы_прокрутки - IDC_RED
		index = GetDlgCtrlID(hCtrl) - IDC_RED;
		switch(LOWORD(wParam))
		{ 
		case SB_LINEUP: // скроллинг на строку вверх
			// уменьшаем цветовую составляющую на единицу
			// и меняем на ноль если получилось отрицательное число
			rgb[index] = max(0, rgb[index] - 1); 
			break; 
		case SB_LINEDOWN: // скроллинг на строку вниз
			// увеличиваем цветовую составляющую на единицу
			// и меняем на 255, если получилось число больше 255
			rgb[index] = min(255, rgb[index] + 1); 
			break; 
		case SB_PAGEUP: // скроллинг на страницу вверх
			// аналогично скроллингу на строку вверх
			rgb[index] = max(0, rgb[index] - 15); 
			break; 
		case SB_PAGEDOWN: // скроллинг на страницу вниз
			// аналогично скроллингу на строку вниз
			rgb[index] = min(255, rgb[index] + 15); 
			break;
		case SB_THUMBTRACK: // обработка перетаскивания движка полосы прокрутки
			// переписываем положение движка в цветовую составляющую
			rgb[index] = HIWORD(wParam); 
			break; 
		}
		// Прокручиваем полосу прокрутки в вычисленную только что позицию
		SetScrollPos(hCtrl, SB_CTL, rgb[index], TRUE); 
		// Сообщаем родительскому окну об изменении цвета фона
		// После получения сообщения родительское окно обновит свой 
		// фоновый цвет в соответствии со значениями в массиве rgb 
		SendMessage(GetParent(hDlg), UM_CHANGE, 0, 0); 
		break; 
		//----------------------------------------------------------------------
	default:
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)TRUE;
}
