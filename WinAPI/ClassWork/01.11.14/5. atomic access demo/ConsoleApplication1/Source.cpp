#include <iostream>
#include <windows.h>
using namespace std;

int x = 50;
int it = 1000000;

DWORD WINAPI f1(void *p)
{
	for (int i = 0; i < it; i++)
    InterlockedDecrement((LPLONG)&x);
	return 0;
}

DWORD WINAPI f2(void *p)
{
	for (int i = 0; i < it; i++)
   InterlockedIncrement((LPLONG)&x);
	return 0;
}

void main()
{
	CreateThread(0,0,f1,0,0,0);
	CreateThread(0,0,f2,0,0,0);

	Sleep(500);
	cout << x << "\n";
}