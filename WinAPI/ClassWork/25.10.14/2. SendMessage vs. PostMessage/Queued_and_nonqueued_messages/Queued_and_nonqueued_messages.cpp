#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");	

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);	
	wcl.style = CS_HREDRAW | CS_VREDRAW;	
	wcl.lpfnWndProc = WindowProc;	
	wcl.cbClsExtra = 0;	
	wcl.cbWndExtra = 0; 	
	wcl.hInstance = hInst;	
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Синхронные и асинхронные сообщения"), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 200, 
		NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);	
		DispatchMessage(&Msg);	
	}
	return Msg.wParam;
}	


LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if(wParam == VK_UP)
			{
				HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
				if(h)
					SendMessage(h, WM_CLOSE, 0, 0);
				// Функция SendMessage отправляет заданное сообщение окну или окнам.
				// Функция вызывает оконную процедуру для заданного окна и не возвращает значение до тех пор,
				// пока оконная процедура не обработает сообщение.
			}
			else if(wParam == VK_DOWN)
			{
				HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
				if(h)
					PostMessage(h, WM_CLOSE, 0, 0);
				// Функция PostMessage помещает(вставляет в очередь) сообщение в очередь сообщений,
				// связанную с потоком, который создал заданное окно и возвращает значение без ожидания потока,
				// который обрабатывает сообщение.

				// http://efrazrabotka.ru/27/

			    // http://www.cyberforum.ru/win-api/thread1155829.html


			}
			else if(wParam == VK_LEFT)
			{
				HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
				if(h)
					SendMessage(h, WM_QUIT, 0, 0);
			}
			else if(wParam == VK_RIGHT)
			{
				HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
				if(h)
					PostMessage(h, WM_QUIT, 0, 0);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}