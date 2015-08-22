#include <windows.h>

HHOOK hook;
HINSTANCE hinstance = NULL;

BOOL WINAPI DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	hinstance = (HINSTANCE)hModule;
	hook = NULL;

	return TRUE;
}

LRESULT CALLBACK hookproc(int ncode, WPARAM wparam, LPARAM lparam)
{
	//������� ��������� ����
	if (ncode == HC_ACTION)
	{
		if ((lparam & 0x80000000) == 0x00000000) //�������� �� ������� ������ (�� �� ������������!)
		{
			HWND hwnd = FindWindow("#32770", "������������ HOOK");//������� ���� ������ ����������
			//� ����� ���������� ����� ���������������� ��������� WM_USER+755
			PostMessage(hwnd, WM_USER + 755, wparam, lparam); //�������� ��������� ���� ����������
		}
	}
	//�������� ��������� ������� �� ������� �����
	return (CallNextHookEx(hook, ncode, wparam, lparam));
}

//������� ��� ��������� ����
extern "C" __declspec(dllexport)
bool installhook()
{
	return hook = SetWindowsHookEx(WH_KEYBOARD, hookproc, hinstance, NULL);
}

extern "C" __declspec(dllexport)
bool removehook()
{
	//������� ���
	return UnhookWindowsHookEx(hook);
}