#include <iostream>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

DWORD WINAPI func1(void *p)
{
	while (true)
	{
		SetConsoleTextAttribute(h, 12);
		cout << "@";
		Sleep(15);
	}
	return 0;
}

DWORD WINAPI func2(void *p)
{
	while (true)
	{
		SetConsoleTextAttribute(h, 9);
		cout << "#";
		Sleep(20);
	}
	return 0;
}

void main()
{
	/*
	HANDLE CreateThread(
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // ��������� �� ���������, ����������� ��������� ������ ������. ���� ��������� ��������� �������� NULL, �� ��������������� �������� �� ���������.
		DWORD dwStackSize, // ������������� ������ �����, ������� ��������� ������. ���� �������� ����� ����, �� ��������������� ����, ������ ����� ���������� ������
		LPTHREAD_START_ROUTINE lpStartAddress, // ����� ������� ��������� �������
		LPVOID lpParameter, // �������������� ��������, ������������ � ��������� �������
		DWORD dwCreationFlags, // ����, ������� ��������� ��������� ������. ���� ���� �������� ����� CREATE_SUSPENDED, �� ����� ����� ���������� ��  ����������� �� ����������.
		LPDWORD lpThreadId  // ����� ���������� ���� DWORD, � ������� ������� ���������� ������������� ������ ������
	);
	*/

	CreateThread(0,0,func1,0,0,0);
	Sleep(3000);

	CreateThread(0,0,func2,0,0,0);
	Sleep(3000);

	while (true)
	{
		SetConsoleTextAttribute(h, 10);
		cout << "!";
		Sleep(500);
	}

}