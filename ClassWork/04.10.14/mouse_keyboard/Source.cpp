#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Mouse and Keyboard");

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof (wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;

	if (!RegisterClassEx(&wcl))
		return 0;

	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("Обработка событий мышки и клавиатуры"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[50];
	switch (uMessage)
	{
	case WM_LBUTTONDBLCLK:
		MessageBox(0,
			TEXT("Двойной щелчок левой кнопкой мыши"),
			TEXT("WM_LBUTTONDBLCLK"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(
			0,
			TEXT("Нажата левая кнопка мыши"),
			TEXT("WM_LBUTTONDOWN"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONUP:
		MessageBox(
			0,
			TEXT("Отпущена левая кнопка мыши"),
			TEXT("WM_LBUTTONUP"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(
			0,
			TEXT("Нажата правая кнопка мыши"),
			TEXT("WM_RBUTTONDOWN"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_MOUSEMOVE:
		wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(hWnd, str);
		break;
	case WM_CHAR:
		wsprintf(str, TEXT("Нажата клавиша %c"), (wchar_t)wParam);	// ASCII-код нажатой клавиши
		MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("Код клавиши %d"), (int)wParam);
		MessageBox(0, str, TEXT("WM_KEYDOWN"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}