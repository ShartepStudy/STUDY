#include <windows.h>
#define __MYDLL__
#include "implicit linking.h"

int counter = 10;

void MessageInfo(char* str)
{
	MessageBox(NULL, str, "Message", MB_OK);
}

void Ref(int& ref)
{
	ref = 67;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	switch (reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			MessageBox(NULL,"������� ��������� DLL � ��� �������� ������������","������ �� DllMain",MB_OK);
			break;
		case DLL_PROCESS_DETACH:
			MessageBox(NULL,"������� ��������� DLL �� ��������� ������������","������ �� DllMain",MB_OK);
			break;
		case DLL_THREAD_ATTACH:
			MessageBox(NULL,"�������� ����� ������� �����","������ �� DllMain",MB_OK);
			break;
		case DLL_THREAD_DETACH:
			MessageBox(NULL,"������� ����� �������� ������","������ �� DllMain",MB_OK);
			break;
	}
	return TRUE;
}
