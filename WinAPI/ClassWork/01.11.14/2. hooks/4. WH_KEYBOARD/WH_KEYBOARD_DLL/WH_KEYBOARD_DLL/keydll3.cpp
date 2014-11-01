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
	//Функция обработки Хука
	if (ncode == HC_ACTION)
	{
		if ((lparam & 0x80000000) == 0x00000000) //Проверка на нажатие кнопки (не на освобождение!)
		{
			HWND hwnd = FindWindow("#32770", "Клавиатурный HOOK");//Находим окно нашего приложения
			//в нашем приложении будет зарегистрировано сообщение WM_USER+755
			PostMessage(hwnd, WM_USER + 755, wparam, lparam); //Посылаем сообщение окну приложения
		}
	}
	//Вызываем следующую функцию из цепочки хуков
	return (CallNextHookEx(hook, ncode, wparam, lparam));
}

//Функция для установки Хука
extern "C" __declspec(dllexport)
bool installhook()
{
	return hook = SetWindowsHookEx(WH_KEYBOARD, hookproc, hinstance, NULL);
}

extern "C" __declspec(dllexport)
bool removehook()
{
	//Удаляем хук
	return UnhookWindowsHookEx(hook);
}