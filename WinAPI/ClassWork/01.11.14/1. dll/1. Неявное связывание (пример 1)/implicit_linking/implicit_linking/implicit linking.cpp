#include <windows.h>
#define __MYDLL__
#include "implicit linking.h"

int counter = 10;

void MessageInfo(char* str)
{
	MessageBoxA(0, str, "Message Box from DLL", MB_OK);
}

void Ref(int& ref)
{
	ref = 67;
}

/*
����� ����� � DLL.
BOOL WINAPI DllMain(  - ���������� ��������� ��� ��� ������������� Dll. �� ������ ������� ������������ TRUE ��� FALSE.
	HINSTANCE hinstDLL,  - ���������� Dll ������
	DWORD fdwReason,  - �������, �� ������� ��� ������ DllMain
		DLL_PROCESS_ATTACH � ��������� ������� ��������� Dll ������ � ���� �������� ������������.
		DLL_PROCESS_DETACH - ��������� ������� ��������� Dll ������
		DLL_THREAD_ATTACH � �������, ������������ Dll, ������� ����� �����
		DLL_THREAD_ DETACH � ��������� ����� �������� �������� ���������� �� ��.
	LPVOID lpvReserved - ���������������
);

���� DllMain ���������� TRUE � ��� ��������, ��� �� ������ �������, 
���� FALSE � ��� ������� ���������� ������� �� ���������� � ��. 
��� �����, LoadLibrary ������ 0. 

��� ������������� TerminateProcess ��� TeriminateThread, ����� ��� �������, 
� �������� ����������� ������ ������� �� ������� ��� ����������� dll ������� DllMain � ����������
DLL_PROCESS_DETACH ��� DLL_THREAD_DETACH. 

������ � DllMain ������������� ��������� ������ ���������� ��������, ����� ���: 
��������� � ������������ ������, �������� � �������� ����� � ������ �������� �� �������������. 
*/

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	switch(reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			MessageBoxA(0, "������� ��������� DLL � ��� �������� ������������", "������ �� DllMain", MB_OK);
			break;
		case DLL_PROCESS_DETACH:
			MessageBoxA(0, "������� ��������� DLL �� ��������� ������������", "������ �� DllMain", MB_OK);
			break;
		case DLL_THREAD_ATTACH:
			MessageBoxA(0, "�������� ����� �����", "������ �� DllMain", MB_OK);
			break;
		case DLL_THREAD_DETACH:
			MessageBoxA(0, "������� ����� �������� ������", "������ �� DllMain", MB_OK);
			break;
	}
	return TRUE;
}
