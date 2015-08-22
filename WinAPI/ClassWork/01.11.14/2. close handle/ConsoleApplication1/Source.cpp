#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>
using namespace std;

void main()
{
	setlocale(0, "");
	TCHAR * strNewProcessName = _T("C:\\Windows\\system32\\cmd.exe");
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));	
	si.cb = sizeof(si);

	BOOL bOk = CreateProcess(strNewProcessName, 0, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi);

	//BOOL bOk = CreateProcess(L"C:\\Windows\\Notepad.exe", L" C:\\Windows\\system32\\drivers\\etc\\hosts", 0, 0, 0, 0, 0, 0, &si, &pi);

	if (bOk)
	{
		_tprintf(_T("Процесс:\n %s \nPID: %u \nHANDLE: %u успешно запущен\n ждём завершения...\n"), strNewProcessName, pi.dwProcessId, pi.hProcess);

		WaitForSingleObject(pi.hProcess, INFINITE); // http://msdn.microsoft.com/ru-ru/library/windows/desktop/ms687032(v=vs.85).aspx
		// The WaitForSingleObject function checks the current state of the specified object. If the object's state is nonsignaled, the calling thread enters the wait state until the object is signaled or the time-out interval elapses.
		_tprintf(_T("Процесс %s PID: %u HANDLE: %u успешно завершен..."), strNewProcessName, pi.dwProcessId, pi.hProcess);

		_getch();

		// Все объекты ядра используют подсчет ссылок для определения момента, когда сам объект можно уничтожить
		// Процесс — объект ядра. Соответственно, пока ты не выполнен CloseHandle, система будет думать,
		// что процесс существует, и в ядре его данные освобождены не будут. Например, если будет необходимо
		// узнать время, когда процесс завершился, на него открывается хэндл и нужно ждать его завершения.
		// После чего можно узнать время завершения, но возможность такая имеется именно потому, что процесс
		// как объект ядра, еще существует (кстати, и его первичный поток, тоже как объект ядра, будет существовать).

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}