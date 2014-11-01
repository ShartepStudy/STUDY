#include <iostream>
#include <windows.h>
using namespace std;

CRITICAL_SECTION cs;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

DWORD WINAPI func1(void *p)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		SetConsoleTextAttribute(h, 12);
		cout << "@";
		Sleep(15);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI func2(void *p)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		SetConsoleTextAttribute(h, 9);
		cout << "#";
		Sleep(15);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

void main()
{
	InitializeCriticalSection(&cs);

	CreateThread(0,0,func1,0,0,0);
	CreateThread(0,0,func2,0,0,0);
	
	while (1)
	{
		
	}

	DeleteCriticalSection(&cs);
}