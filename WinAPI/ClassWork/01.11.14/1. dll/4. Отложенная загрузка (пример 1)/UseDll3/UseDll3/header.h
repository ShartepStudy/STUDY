
#include <windows.h>
#include "resource.h"

#include <delayimp.h>
#include "implicit linking.h"
#pragma comment (lib, "Delayimp.lib") // Подключение lib файла для отложенной загрузки
#pragma comment (lib, "implicit_linking.lib")

/*

Отложенная загрузка (Delay Loaded DLL) использует преимущество и явной, и неявной загрузки. 
Существует возможность загрузить DLL только когда это необходимо и выгрузить по желанию.
Для использования отложенной загрузки существует специальный DLL и LIB файл под названием delayimp.lib и delayimp.dll. 
Для подключения пользовательской DLL необходимо:
Properties->Linker->Input->Delay Loaded dll (implicit_linking.dll)

Для выгрузки из памяти dll необходимо:
1. Подключить файл #include "delayimp.h"
2. Properties->Linker->Advanced->Delay Loaded Dll (Support Unload (/DELAY:UNLOAD))

*/
