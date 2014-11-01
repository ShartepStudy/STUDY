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
Точка входа в DLL.
BOOL WINAPI DllMain(  - вызывается несколько раз при использовании Dll. Из данной функции возвращается TRUE или FALSE.
	HINSTANCE hinstDLL,  - дескриптор Dll модуля
	DWORD fdwReason,  - причина, по которой был вызван DllMain
		DLL_PROCESS_ATTACH – некоторый процесс загружает Dll модуль в свое адресное пространство.
		DLL_PROCESS_DETACH - некоторый процесс выгружает Dll модуль
		DLL_THREAD_ATTACH – процесс, использующий Dll, породил новый поток
		DLL_THREAD_ DETACH – некоторый поток текущего процесса выгрузился из ОП.
	LPVOID lpvReserved - зарезервировано
);

Если DllMain возвращает TRUE – это означает, что всё прошло успешно, 
если FALSE – при неявном связывании процесс не загрузится в ОП. 
При явном, LoadLibrary вернет 0. 

При использовании TerminateProcess или TeriminateThread, поток или процесс, 
к которому применяется данная функция не вызовет для загруженных dll функцию DllMain с аргументом
DLL_PROCESS_DETACH или DLL_THREAD_DETACH. 

Обычно в DllMain рекомендуется исполнять только простейшие операции, такие как: 
выделение и освобождение памяти, открытие и закрытие файла и другие операции по инициализации. 
*/

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	switch(reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			MessageBoxA(0, "Процесс загружает DLL в своё адресное пространство", "Привет из DllMain", MB_OK);
			break;
		case DLL_PROCESS_DETACH:
			MessageBoxA(0, "Процесс выгружает DLL из адресного пространства", "Привет из DllMain", MB_OK);
			break;
		case DLL_THREAD_ATTACH:
			MessageBoxA(0, "Порожден новый поток", "Привет от DllMain", MB_OK);
			break;
		case DLL_THREAD_DETACH:
			MessageBoxA(0, "Фоновый поток завершил работу", "Привет от DllMain", MB_OK);
			break;
	}
	return TRUE;
}
