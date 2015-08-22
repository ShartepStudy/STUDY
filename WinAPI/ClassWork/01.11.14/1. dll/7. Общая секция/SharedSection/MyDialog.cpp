#include "MyDialog.h"

// По умолчанию для большей безопасности глобальные и статические данные не разделяются несколькими проекциями
// одного и того же EXE или DLL. Но иногда удобнее, чтобы несколько проекций EXE разделяли единственный экземпляр переменной.
// Существует метод, обеспечивающий совместное использование переменных всеми экземплярами EXE или DLL.
// Любой образ EXE - или DLL - файла состоит из группы разделов. По соглашению имя каждого стандартного раздела начинается
// с точки. Например, при компиляции программы весь код помещается в раздел.text, не инициализированные данные - в раз дел.bss,
// а инициализированные — в раздел.data. Кроме стандартных разделов, генерируемых компилятором и компоновщиком, можно создавать
// свои разделы в EXE - или DLL - файле, используя директиву компилятора:
// #pragma data_seg("имя_раздела") 
// Чаще всего переменные помещают в собственные разделы, намереваясь сделать их разделяемыми между несколькими проекциями EXE
// или DLL. По умолчанию каждая проекция получает свой набор переменных. Но можно сгруппировать в отдельном разделе переменные,
// которые должны быть доступны всем проекциям EXE или DLL; тогда система не станет создавать новые экземпляры этих переменных
// для каждой проекции EXE или DLL.
// Чтобы переменные стали разделяемыми, одного указания компилятору выделить их в какой - то раздел мало. Надо также сообщить
// компоновщику, что переменные в этом разделе должны быть общими. Для этого предназначен ключ / SECTION компоновщика
// SECTION:имя, атрибуты
// За двоеточием укажите имя раздела, атрибуты которого Вы хотите изменить.
// http://msdn.microsoft.com/en-us/library/sf9b18xk(v=vs.90).aspx

#pragma data_seg("my_shared_section")
int counter = 0;
#pragma data_seg()
#pragma comment (linker, "/SECTION:my_shared_section,RWS")

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog()
{
	ptr = this;
	++counter;
}

CMyDialog::~CMyDialog()
{
	--counter;
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
}

void CMyDialog::OnCommand(WPARAM wp, LPARAM lp)
{
	if (LOWORD(wp) == IDC_BUTTON1)
	{
		char str[50];
		wsprintf(str, "Количество запущенных экземпляров приложения: %d", counter);
		MessageBox(hDialog, str, "Общая секция", MB_OK | MB_ICONINFORMATION);
	}
}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	case WM_INITDIALOG:
		ptr->OnInitDialog(hWnd);
		break;
	case WM_COMMAND:
		ptr->OnCommand(wp, lp);
		break;
	}
	return 0;
}