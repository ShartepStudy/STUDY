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
		_tprintf(_T("�������:\n %s \nPID: %u \nHANDLE: %u ������� �������\n ��� ����������...\n"), strNewProcessName, pi.dwProcessId, pi.hProcess);

		WaitForSingleObject(pi.hProcess, INFINITE); // http://msdn.microsoft.com/ru-ru/library/windows/desktop/ms687032(v=vs.85).aspx
		// The WaitForSingleObject function checks the current state of the specified object. If the object's state is nonsignaled, the calling thread enters the wait state until the object is signaled or the time-out interval elapses.
		_tprintf(_T("������� %s PID: %u HANDLE: %u ������� ��������..."), strNewProcessName, pi.dwProcessId, pi.hProcess);

		_getch();

		// ��� ������� ���� ���������� ������� ������ ��� ����������� �������, ����� ��� ������ ����� ����������
		// ������� � ������ ����. ��������������, ���� �� �� �������� CloseHandle, ������� ����� ������,
		// ��� ������� ����������, � � ���� ��� ������ ����������� �� �����. ��������, ���� ����� ����������
		// ������ �����, ����� ������� ����������, �� ���� ����������� ����� � ����� ����� ��� ����������.
		// ����� ���� ����� ������ ����� ����������, �� ����������� ����� ������� ������ ������, ��� �������
		// ��� ������ ����, ��� ���������� (������, � ��� ��������� �����, ���� ��� ������ ����, ����� ������������).

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}