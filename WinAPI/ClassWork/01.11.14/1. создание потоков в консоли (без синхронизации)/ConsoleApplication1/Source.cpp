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
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // указатель на структуру, описывающую параметры защиты потока. ≈сли параметру присвоено значение NULL, то устанавливаютс€ атрибуты по умолчанию.
		DWORD dwStackSize, // устанавливает размер стека, который отводитс€ потоку. ≈сли параметр равен нулю, то устанавливаетс€ стек, равный стеку первичного потока
		LPTHREAD_START_ROUTINE lpStartAddress, // адрес входной потоковой функции
		LPVOID lpParameter, // дополнительный параметр, передаваемый в потоковую функцию
		DWORD dwCreationFlags, // флаг, который управл€ет созданием потока. ≈сли этот параметр равен CREATE_SUSPENDED, то поток после порождени€ не  запускаетс€ на исполнение.
		LPDWORD lpThreadId  // адрес переменной типа DWORD, в которую функци€ возвращает идентификатор нового потока
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