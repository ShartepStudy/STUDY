#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

char str[16];
CRITICAL_SECTION cs;

DWORD WINAPI f1(void *p)
{
	EnterCriticalSection(&cs);
	int len = strlen(str);
	for (int i = len; i < len + 5; i++){
		str[i] = '1';
		cout << "\n1: " << str << endl;
		Sleep(20);
	}
	str[len + 5] = '\0';
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI f2(void *p)
{
	while (!TryEnterCriticalSection(&cs))
	{
		cout << "f2 attempt!\n";
		Sleep(5);
	}

	int len = strlen(str);
	for (int i = len; i < len + 5; i++){
		str[i] = '2';
		cout << "\n2: " << str << endl;

		Sleep(10);
	}
	str[len + 5] = '\0';
	LeaveCriticalSection(&cs);

	return 0;
}

void main()
{
	HANDLE hThreads[2];
	InitializeCriticalSection(&cs);
	hThreads[0] = CreateThread(0, 0, f1, 0, 0, 0);
	hThreads[1] = CreateThread(0, 0, f2, 0, 0, 0);
	
	int index = WaitForMultipleObjects(2, hThreads, true, INFINITE);

	cout << index  << "Thread finished!\n";

	cout << str << "\n";
	DeleteCriticalSection(&cs);
}