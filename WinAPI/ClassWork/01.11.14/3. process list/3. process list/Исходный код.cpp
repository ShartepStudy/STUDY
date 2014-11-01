#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <Tlhelp32.h>
#include <conio.h>

void ProcessList()
{
	// http://gsmtut.narod.ru/os/20.htm

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe;
	memset(&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(pe);
	if (Process32First(hSnapShot, &pe))
	{
		_tprintf(_T("ID:  %4u  Threads: %5u   priority:  %2u    name:   %s\n"), pe.th32ProcessID, pe.cntThreads, pe.pcPriClassBase, pe.szExeFile);

		while (Process32Next(hSnapShot, &pe))
		{
			_tprintf(_T("ID:  %4u  Threads: %5u   priority:  %2u    name:   %s\n"), pe.th32ProcessID, pe.cntThreads, pe.pcPriClassBase, pe.szExeFile);
		}
	}
}

void main()
{
	setlocale(LC_ALL, "");
	ProcessList();
}

