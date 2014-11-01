#include "windows.h"
#include "iostream"
#include "conio.h"
using namespace std;

HANDLE hSem;

DWORD WINAPI f(LPVOID p)
{
	WaitForSingleObject(hSem, INFINITE);
	int No = (int)p;

	cout << No;
	cout << "\n";

	Sleep(5000);

	ReleaseSemaphore(hSem, 1, 0);
	return 0;
}


void main()
{
	hSem = CreateSemaphore(0, 5, 5, 0);
	HANDLE hLast;
	for (int i = 0; i < 100; i++)
	{
		hLast = CreateThread(0, 0, f, (void*)i, 0, 0);
	}
	
	WaitForSingleObject(hLast, INFINITE);
}