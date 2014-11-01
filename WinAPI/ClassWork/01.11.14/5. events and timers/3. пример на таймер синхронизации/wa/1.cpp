// файл windows.h содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows.
// без этой библиотеки приложение не запустится.
#include <windows.h>
#include <tchar.h>

// прототип оконной процедуры, которая занимается обработкой сообщений
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Запуск процесса");

// точка входа в приложение
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wcl;

	// 1. определение класса окна
	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX
	// перерисовать всё окно, если изменяется размер по горизонтали или по вертикали
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - стиль класса окна
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra  = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// загрузка стандартного курсора	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	// заполнение окна белым цветом
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна

	// 2. регистрация класса окна
	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// 3. создание окна
	// создается окно и  переменной hWnd присваивается дескриптор окна
	HWND hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	//имя класса окна
		szClassWindow, // заголовок окна
		WS_OVERLAPPEDWINDOW,				// стиль окна
		// заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения

	// 4. отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // перерисовка окна

	// 5. запуск цикла обработки сообщений
	MSG lpMsg;
	while(GetMessage(&lpMsg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений
	{
		TranslateMessage(&lpMsg);	// трансляция сообщения
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
	}
	return lpMsg.wParam;
}	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0); // посылка сообщения WM_QUIT
		break;
	case WM_CREATE:
		{
			SECURITY_ATTRIBUTES sa;
			sa.nLength = sizeof(SECURITY_ATTRIBUTES); // размер структуры
			sa.lpSecurityDescriptor = 0; // система защиты по умолчанию
			sa.bInheritHandle = TRUE; // дескриптор объекта ядра "файл" - наследуемый

			HANDLE hHandle = CreateFile(
				TEXT("C:\\Cars.xml"), // путь к файлу
				GENERIC_READ, // только чтение
				0, // запрет совместного использования файла
				&sa, //атрибуты защиты объекта ядра «файл»
				OPEN_EXISTING, // открытие существующего файла
				FILE_ATTRIBUTE_NORMAL, // атрибутов нет 
				NULL // обычно используется в клиент-серверном приложении
				);

			if ( hHandle == INVALID_HANDLE_VALUE ){ //ошибка открытия файла
				MessageBox(0,L"OOPS!",L"Smth wrong!",0);
				return 0;
			}

			STARTUPINFO startin = {sizeof(STARTUPINFO)};
			PROCESS_INFORMATION info = {0};

			TCHAR cmd[20];
			//дескриптор объекта ядра передается дочернему процессу через командную строку
			wsprintf(cmd, TEXT("%s %d"), TEXT("child.exe"), hHandle);

			CreateProcess(
				NULL, // в качестве имени файла выступает первая выделенная пробелами лексема из 2-го параметра
				cmd, // Указатель командной строки, содержащей, в том числе, имя исполняемого файла
				NULL, // атрибуты защиты процесса по умолчанию
				NULL, // атрибуты защиты потока по умолчанию
				TRUE, // наследование дескрипторов объектов ядра разрешено
				0, // класс приоритета по умолчанию - NORMAL_PRIORITY_CLASS 
				NULL, // среда окружения наследуется у родительского процесса 
				NULL, // текущий каталог наследуется у родительского процесса 
				&startin, //способ отображения главного окна, а также размер и заголовок окна
				&info // информация о порождённом процессе
				);
			CloseHandle(hHandle); // закрывается описатель объекта ядра «файл»
			CloseHandle(info.hThread); // закрывается описатель объекта ядра «поток»
			CloseHandle(info.hProcess); // закрывается описатель объекта ядра «процесс»

		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}