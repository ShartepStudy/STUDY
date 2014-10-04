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
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщени€ о двойном щелчке (DBLCLK)
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
		TEXT("ќбработка событий мышки и клавиатуры"),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		400,
		400,
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
	HWND hw;

	switch (uMessage)
	{

	case WM_LBUTTONDOWN:
		RECT r;
		GetWindowRect(hWnd, &r);
		wsprintf(str, TEXT("X1=%d Y1=%d X2=%d Y2=%d"), r.left, r.top, r.right, r.bottom);

		MessageBox(0,
			str,
			L" оординаты окна",
			MB_OK | MB_ICONINFORMATION);

		GetClientRect(hWnd, &r);
		wsprintf(str, TEXT("X1=%d Y1=%d X2=%d Y2=%d"), r.left, r.top, r.right, r.bottom);

		MessageBox(0,
			str,
			L" оординаты клиентской области окна",
			MB_OK | MB_ICONINFORMATION);

		////////////

		MoveWindow(hWnd, 50, 50, 200, 200, true);

		////////////

		hw = FindWindow(L"CalcFrame", L" алькул€тор");
		BringWindowToTop(hw);
		MoveWindow(hw, 150, 150, 200, 200, true);

		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}