// файл windows.h содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows.
// без этой библиотеки приложение не запустится.
#include <windows.h>

// позволяет использовать как ANSI-кодировку, так и Unicode.
#include <tchar.h>

// позволяет использовать функцию time, для генерации случайных чисел.
#include <time.h>

// прототип оконной процедуры, которая занимается обработкой сообщений
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");	// имя класса окна

// точка входа в приложение
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	// 1. определение класса окна
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);	// размер в байтах структуры WNDCLASSEX
	// перерисовать всё окно, если изменён размер по горизонтали или по вертикали
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - стиль класса окна (CS_DBLCLKS!)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры, указатель на функцию WindowProc
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки (посмотреть список иконок!)
	// #include "resource.h" // пользовательская иконка
	// HINSTANCE hIns=GetModuleHandle(0);
	// HICON hIcon=LoadIcon(hIns,MAKEINTRESOURCE(IDI_ICON1));
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// загрузка стандартного курсора (посмотреть список курсоров!)
	// HCURSOR hCursor=LoadCursorFromFile(L"C:\\1.ani");
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// заполнение окна белым цветом - ЗАДАТЬ ФОНОВЫЙ ЦВЕТ
	//wcl.hbrBackground=CreateSolidBrush (RGB(255,120,0)); // любой цвет
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна

	// 2. регистрация класса окна
	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// 3. создание окна
	// создается окно и переменной hWnd присваивается дескриптор окна

	//srand(time(0));
	//wchar_t*s=new wchar_t[200];
	//int test=rand()%50;
	//_itow(test,s,10);

	HWND hWnd = CreateWindowEx(
		0,		// расширенный стиль окна (WS_EX_ACCEPTFILES, WS_EX_CLIENTEDGE)
		szClassWindow,	//имя класса окна
		TEXT("Каркас окна!"), // заголовок окна
		WS_OVERLAPPEDWINDOW, // стиль окна (WS_HSCROLL | WS_VSCROLL)
		// заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна
		0, 0, rand() % 200 + 200, rand() % 200 + 200,
		//CW_USEDEFAULT,    // х-координата левого верхнего угла окна
		//CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		//CW_USEDEFAULT,	// ширина окна
		//CW_USEDEFAULT,	// высота окна
		HWND_DESKTOP,			// дескриптор родительского окна (HWND_DESKTOP)
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения


	// 4. отображение окна
	FLASHWINFO info;
	info.cbSize = sizeof(info);
	info.hwnd = hWnd;
	info.dwFlags = FLASHW_ALL;
	info.dwTimeout = 0;
	info.uCount = 5;

	ShowWindow(hWnd, nCmdShow);
	FlashWindowEx(&info);

	UpdateWindow(hWnd); // перерисовка окна

	/*#define SW_HIDE             0
	#define SW_SHOWNORMAL       1
	#define SW_NORMAL           1
	#define SW_SHOWMINIMIZED    2
	#define SW_SHOWMAXIMIZED    3
	#define SW_MAXIMIZE         3
	#define SW_SHOWNOACTIVATE   4
	#define SW_SHOW             5
	#define SW_MINIMIZE         6
	#define SW_SHOWMINNOACTIVE  7
	#define SW_SHOWNA           8
	#define SW_RESTORE          9
	#define SW_SHOWDEFAULT      10
	#define SW_FORCEMINIMIZE    11
	#define SW_MAX              11*/

	/* // добавление менюшки (по желанию)
	HMENU main_menu = CreateMenu();
	HMENU menu_help = CreatePopupMenu();
	HMENU menu_view = CreatePopupMenu();
	AppendMenu(main_menu, MF_STRING | MF_POPUP, (UINT)menu_view, L"Просмотр");
	AppendMenu(main_menu, MF_STRING | MF_POPUP, (UINT)menu_help, L"Справка");
	AppendMenu(menu_help, MF_STRING, 1001, L"О программе...");
	AppendMenu(menu_view, MF_STRING, 1002, L"Текст");
	AppendMenu(menu_view, MF_STRING, 1003, L"Графика");
	SetMenu(hWnd, main_menu);
	*/

	// 5. запуск цикла обработки сообщений

	MSG lpMsg;
	while (GetMessage(&lpMsg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений (пока не придёт WM_QUIT)
	{ // выбирать любые сообщения из любых приложений
		TranslateMessage(&lpMsg);	// трансляция сообщения (потребуется для работы с клавиатурой)
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
	} // отправка сообщения оконной процедуре
	return lpMsg.wParam;
}

// функция вызывается ОС, не программой!
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0); // посылка сообщения WM_QUIT
		break;
	case WM_CLOSE:
		MessageBoxA(0, "Ha-Ha", "Я не закроюсь!", MB_OK);
		break;
	default:
		// все сообщения, которые не обрабатываются в данной оконной функции 
		// направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}