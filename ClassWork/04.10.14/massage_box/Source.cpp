#include <windows.h>
#include <tchar.h>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	int res = MessageBox(0, TEXT("����� �� ������� 1"), TEXT("����� ��������� 1"), MB_OKCANCEL | MB_ICONASTERISK);
	if (res == IDOK) MessageBox(0, TEXT("����� �� ������� 2"), TEXT("����� ��������� 2"), MB_OK | MB_ICONSTOP);
	return 0;
}