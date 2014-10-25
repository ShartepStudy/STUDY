// файл windows.h содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows.
// без этой библиотеки приложение не запустится.
#include <windows.h>

// позволяет использовать как ANSI-кодировку, так и Unicode.
#include <tchar.h>

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
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// загрузка стандартного курсора (посмотреть список курсоров!)
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// заполнение окна белым цветом - ЗАДАТЬ ФОНОВЫЙ ЦВЕТ
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна

	// 2. регистрация класса окна
	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// 3. создание окна
	// создается окно и переменной hWnd присваивается дескриптор окна

	HWND hWnd = CreateWindowEx(
		0,		// расширенный стиль окна (WS_EX_ACCEPTFILES, WS_EX_CLIENTEDGE)
		szClassWindow,	//имя класса окна
		TEXT("Супер Графика"), // заголовок окна
		WS_OVERLAPPEDWINDOW, // стиль окна (WS_HSCROLL | WS_VSCROLL)
		// заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна
		//0,0,rand()%200+200, rand()%200+200,
		CW_USEDEFAULT,    // х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		HWND_DESKTOP,			// дескриптор родительского окна (HWND_DESKTOP)
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения


	// 4. отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // перерисовка окна

	// 5. запуск цикла обработки сообщений

	MSG lpMsg;
	while (GetMessage(&lpMsg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений (пока не придёт WM_QUIT)
	{ // выбирать любые сообщения из любых приложений
		TranslateMessage(&lpMsg);	// трансляция сообщения (потребуется для работы с клавиатурой)
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
	} // отправка сообщения оконной процедуре
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	switch (uMessage)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		MessageBox(0, TEXT("текст на диалоге 1"), TEXT("текст заголовка 1"), MB_OKCANCEL | MB_ICONEXCLAMATION);
//		BlockInput(true);
//		ExitWindowsEx(EWX_LOGOFF, 0); //перезагрузка компьютера
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
