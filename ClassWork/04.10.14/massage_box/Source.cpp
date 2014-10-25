#include <windows.h>
#include <tchar.h>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	int res = MessageBox(0, TEXT("текст на диалоге 1"), TEXT("текст заголовка 1"), MB_OKCANCEL | MB_ICONASTERISK);
	if (res == IDOK) MessageBox(0, TEXT("текст на диалоге 2"), TEXT("текст заголовка 2"), MB_OK | MB_ICONSTOP);
	return 0;
}