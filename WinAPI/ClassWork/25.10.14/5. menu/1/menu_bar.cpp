#include "menu_dlg.h"

CMenuBarDlg* CMenuBarDlg::ptr = NULL;

CMenuBarDlg::CMenuBarDlg(void)
{
	ptr = this;
	bShowStatusBar = TRUE;
}

void CMenuBarDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMenuBarDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	// дескриптор текстового поля
	hEdit = GetDlgItem(hDialog, IDC_EDIT2);
	// загрузка меню из ресурсов приложения
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2));
	// присоединение меню к главному окну приложения
	SetMenu(hDialog, hMenu);
	return TRUE;
}

// обработчик сообщения WM_COMMAND будет вызван при выборе пункта меню
void CMenuBarDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_UNDO:
		// отмена последнее действие
		SendMessage(hEdit, WM_UNDO, 0, 0); 
		break;
	case ID_CUT:
		// "вырезание" выделенного фрагмента текста
		SendMessage(hEdit, WM_CUT, 0, 0); 
		break;
	case ID_COPY:
		// копирование выделенного фрагмента текста в буфер обмена
		SendMessage(hEdit, WM_COPY, 0, 0); 
		break;
	case ID_PASTE:
		// вставка текста в Edit Control из буфера обмена
		SendMessage(hEdit, WM_PASTE, 0, 0); 
		break;
	case ID_DEL:
		// удаление выделенного фрагмента текста
		SendMessage(hEdit, WM_CLEAR, 0, 0); 
		break;
	case ID_SELECTALL:
		// выделение всего текста в Edit Control
		SendMessage(hEdit, EM_SETSEL, 0, -1); 
		break;
	}
}

// обработчик сообщения WM_SIZE будет вызван при изменении размеров главного окна
// либо при сворачивании/восстановлении главного окна
void CMenuBarDlg::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rect1;
	// получение координат клиентской области главного окна
	GetClientRect(hDialog, &rect1);
	// установка новых размеров текстового поля
	MoveWindow(hEdit, rect1.left, rect1.top, rect1.right, rect1.bottom, 1);
}

// обработчик WM_INITMENUPOPUP будет вызван непосредственно 
// перед активизацией всплывающего меню
void CMenuBarDlg::Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu) 
{
	if(item == 0) // активизируется пункт меню "Правка"
	{
		// границы выделения текста
		DWORD dwPosition = SendMessage(hEdit, EM_GETSEL, 0, 0); 
		WORD wBeginPosition = LOWORD(dwPosition);
		WORD wEndPosition = HIWORD(dwPosition);

		if(wEndPosition != wBeginPosition) // текст выделен?
		{
			// если да,
			// то разрешёнными будут пункты меню "Копировать", "Вырезать" и "Удалить"
			EnableMenuItem(hMenu, ID_COPY, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, ID_CUT, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, ID_DEL, MF_BYCOMMAND | MF_ENABLED );
		}
		else
		{
			// а если нет,
			// то пункты меню "Копировать", "Вырезать" и "Удалить" будут недоступными
			EnableMenuItem(hMenu, ID_COPY, MF_BYCOMMAND | MF_GRAYED );
			EnableMenuItem(hMenu, ID_CUT, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, ID_DEL, MF_BYCOMMAND | MF_GRAYED);
		}

		if(IsClipboardFormatAvailable(CF_TEXT)) // имеется ли текст в буфере обмена?
			// если да,
			// то пункт меню "Вставить" будет разрешённым
			EnableMenuItem(hMenu, ID_PASTE, MF_BYCOMMAND | MF_ENABLED);
		else 
			// если нет,
			// то пункт меню "Вставить" не будет разрешённым
			EnableMenuItem(hMenu, ID_PASTE, MF_BYCOMMAND | MF_GRAYED);

		// можно сделать отмену?
		if(SendMessage(hEdit, EM_CANUNDO, 0, 0)) 
			// если да - "отмена" разрешена
			// 
			EnableMenuItem(hMenu, ID_UNDO, MF_BYCOMMAND | MF_ENABLED);
		else 
			EnableMenuItem(hMenu, ID_UNDO, MF_BYCOMMAND | MF_GRAYED);

		// длина текста в Edit Control
		int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0); 
		// выделен весь текст в Edit Control?
		if(length != wEndPosition - wBeginPosition) 
			// если не весь
			EnableMenuItem(hMenu, ID_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
		else 
			EnableMenuItem(hMenu, ID_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
	}
}

BOOL CALLBACK CMenuBarDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
		HANDLE_MSG(hwnd, WM_INITMENUPOPUP, ptr->Cls_OnInitMenuPopup);
	}
	return FALSE;
}