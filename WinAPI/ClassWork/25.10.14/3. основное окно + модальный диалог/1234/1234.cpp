#include <windows.h>
#include "resource.h"

// дескриптор модального окна
HWND hDlgModal;

// прототипы процедуры главного окна и модального диалогового окона
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcModal(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// создание главного окна
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = L"Основное окно";

	//регистрируем класс окна
	RegisterClass(&w);

	hwnd = CreateWindow(w.lpszClassName, w.lpszClassName, WS_OVERLAPPEDWINDOW, 10, 10, 290, 100, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// добавление кнопки на главное окно
	CreateWindow(L"Button", L"Создать модальный диалог!", WS_CHILD | WS_VISIBLE, 10, 10, 250, 30, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

	//запускаем цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (hDlgModal == 0 || !IsDialogMessage(hDlgModal, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
	case WM_PAINT:
		break;
	case WM_COMMAND:
		if (HIWORD(wparam) == BN_CLICKED) // если была нажата кнопка
		{
			switch (LOWORD(wparam))
			{ 			// и это кнопка создания модального окна
			case ID_BUTTON:
				// создать модальное окно
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProcModal);
				break;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}

BOOL CALLBACK DlgProcModal(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		// заголовок диалога
		SetWindowText(hDlg, TEXT("Модальный диалог"));
		return TRUE;
	case WM_CLOSE:
		// закрытие
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hDlg, L"на диалоге нажата кнопка OK !", L"сообщение модального окна", MB_OK);
			break;

		case IDCANCEL:
			MessageBox(hDlg, L"на диалоге нажата кнопка Cancel !", L"сообщение модального окна", MB_OK);
			//закрываем окно
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}