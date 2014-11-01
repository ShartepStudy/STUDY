#include "MyDialog.h"

CMyDialog* CMyDialog::ptr;

CMyDialog::CMyDialog()
{
	ptr = this;
	pathes.clear();
}

CMyDialog::~CMyDialog()
{
	for (int i = 0; i < pathes.size(); i++)
		delete[]pathes[i];
	pathes.clear();
}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog = h;
	LoadData();
}

void CMyDialog::OnOpenDialog()
{
	HMENU hMain = GetMenu(hDialog);
	HMENU hSubMenu = GetSubMenu(hMain, 0);

	if (pathes.size() == 0)
		DeleteMenu(hSubMenu, 0, MF_BYPOSITION);

	char *PathName = new char[MAX_PATH];
	ZeroMemory(PathName, MAX_PATH);
	char FileTitle[MAX_PATH];

	OPENFILENAME open = { sizeof(OPENFILENAME) };
	open.hwndOwner = hDialog;
	open.lpstrFilter = "Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0";
	open.lpstrFile = PathName;
	open.nMaxFile = MAX_PATH;
	open.lpstrFileTitle = FileTitle;
	open.nMaxFileTitle = MAX_PATH;
	open.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	open.lpstrDefExt = "txt";

	if (GetOpenFileName(&open))
	{
		string str = "Вы выбрали для открытия файл:\n";
		str += PathName;
		MessageBox(hDialog, str.c_str(), "Диалог Открыть", MB_OK);
		for (int j = 0; j < pathes.size(); j++)
		{
			if (!strcmp(pathes[j], PathName))
			{
				delete[]PathName;
				return;
			}
		}
		AppendMenu(hSubMenu, MF_STRING, WM_USER + pathes.size(), FileTitle);
		pathes.push_back(PathName);
	}
	else
		delete[]PathName;

}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_COMMAND:
		if (LOWORD(wp) == IDC_BUTTON1)
			ptr->OnOpenDialog();
		break;
	case WM_CLOSE:
		ptr->OnClose();
		break;
	case WM_INITDIALOG:
		ptr->OnInitDialog(hWnd);
		break;
	}
	return 0;
}

void CMyDialog::OnClose()
{
	SaveData();
	EndDialog(hDialog, 0);
}

void CMyDialog::SaveData()
{
	HKEY key;
	LONG Result;
	Result = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\БПВ-1321\\Registry", 0, 0, 0, KEY_ALL_ACCESS, 0, &key, 0);
	if (Result != ERROR_SUCCESS)
		return;

	char Name[10];
	DWORD size = pathes.size();

	if (size != 0)
	{
		RegSetValueEx(key, "Quantity", 0, REG_DWORD, (const BYTE*)&size, sizeof(size));
		for (int i = 0; i < size; i++)
		{
			wsprintf(Name, "Path%d", i);
			Result = RegSetValueEx(key, Name, 0, REG_SZ, (const BYTE*)pathes[i], strlen(pathes[i]) + 1);
		}
	}
	RegCloseKey(key);
}

void CMyDialog::LoadData()
{
	/*
	Наиболее часто используемые функции для работы с реестром:
	RegCreateKeyEx    создание нового ключа (раздела);
	RegOpenKeyEx    открытие существующего ключа;
	RegCloseKey    закрытие ключа;
	RegSetValueEx    установка значения параметра;
	RegQueryValueEx    чтение значения параметра;
	RegEnumKeyEx    получить список подключей (подразделов) данного ключа;
	RegEnumValue    получить список параметров данного ключа;
	RegDeleteKey    удалить ключ;
	RegDeleteValue    удалить параметр.
	Если есть два варианта одной и той же функции, то пользоваться нужно "Ex"-вариантом
	*/

	/*
	Функция создает раздел реестра.
	Если раздел уже существует, функция открывает его.
	Имена разделов не чувствительны к регистру.

	RegCreateKeyEx(
	1) HKEY hKey,
	2) LPCTSTR lpSubKey,
	3) DWORD Reserved,
	4) LPTSTR lpClass,
	5) DWORD dwOptions,
	6) REGSAM samDesired,
	7) LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	8) PHKEY phkResult,
	9) LPDWORD lpdwDisposition)

	1) hKey Описатель открываемого раздела.
	2) lpSubKey Указатель на строку, завершающуюся нулевым байтом, которая содержит имя создаваемого или открываемого раздела.
	3) Reserved Зарезервировано - 0.
	4) lpClass Указатель на строку, завершающуюся нулевым байтом, которая содержит класс этого раздела. Может быть проигнорирован и равен NULL. Используется для подключения к удаленному реестру.
	5) dwOptions Параметр может принимать следующие значения.
	REG_OPTION_BACKUP_RESTORE Если флаг установлен, функция игнорирует параметр samDesired и пытается открыть раздел с правами, для резервного копирования и восстановления раздела. Если поток вызывает функцию, обладая привилегией SE_BACKUP_NAME, то раздел открывается с правами доступа ACCESS_SYSTEM_SECURITY и KEY_READ. Если вызывающий поток обладает привилегией SE_RESTORE_NAME, то раздел открывается с правами доступа ACCESS_SYSTEM_SECURITY и KEY_WRITE. Если поток обладает обоими привилегиями, то раздел открывается с комбинированными правами доступа.
	REG_OPTION_VOLATILE Раздел, созданный с помощью этого флага - изменчив. При этом информация сохраняется в памяти и не сохраняется, когда соответствующий улей выгружается. Для HKEY_LOCAL_MACHINE, это происходит, когда компьютер выключается или перезагружается. Для разделов реестра, загруженных функцией RegLoadKey, это происходит, когда выполнена функция RegUnLoadKey. Функция RegSaveKey не сохраняет изменчивые разделы реестра. Этот флаг игнорируется, если раздел уже существует.
	REG_OPTION_NON_VOLATILE Раздел, созданный с помощью этого флага - не изменяем. При этом информация записывается в файл реестра. Функция RegSaveKey сохраняет не изменчивые разделы.

	6) samDesired Определяет права доступа для создаваемого раздела.
	7) lpSecurityAttributes Указатель на структуру SECURITY_ATTRIBUTES. Если параметр равен NULL, то описатель раздела не наследуется порожденным (дочерним) процессом. В эту структуру, входит дескриптор защиты раздела. Если параметр равен NULL, раздел получает дескриптор защиты по умолчанию. Список управления доступом (ACL) в заданном по умолчанию дескрипторе защиты для раздела, наследуются от родительского раздела.
	8) phkResult Указатель на переменную, получающую описатель открытого или созданного раздела.
	9) lpdwDisposition Указатель на переменную, в которую записывается одно из следующих значений.

	REG_CREATED_NEW_KEY Раздел не существует и будет создан
	REG_OPENED_EXISTING_KEY Раздел существует


	Если открытие произошло успешно, функция вернет ERROR_SUCCESS, в противном случае вернет ненулевой код ошибки, определенный в Winerror.h

	После получения описателя раздела реестра с ним проделывают нужные действия, например считывают или записывают значения параметров. После проделанных операций описатель раздела реестра должен быть корректно закрыт. Для этого существует функция RegCloseKey, прототип которой показан ниже.
	*/

	/*
	Функция возвращает информацию о параметре раздела и значение этого параметра.

	LONG RegQueryValueEx(
	1) HKEY hKey,
	2) LPCTSTR lpValueName,
	3) LPDWORD lpReserved,
	4) LPDWORD lpType,
	5) LPBYTE lpData,
	6) LPDWORD lpcbData)

	1) hKey Описатель открытого раздела. Раздел должен быть открыт с правами KEY_QUERY_VALUE.
	2) lpValueName Указатель на С-строку, содержащую название параметра, о котором получается информация. Если параметр - NULL или пустая строка, то возвращается информация о параметре по умолчанию.
	3) lpReserved Зарезервирован - NULL.
	4) lpType Указатель на переменную, которая получает тип данных, сохраненных в параметре. Если равен NULL, то соответственно, информация не возвращается.
	5) lpData Указатель на массив, получающий данные параметра. Если параметр - NULL, то данные не возвращаются. Если данные - это строка, то функция проверяет наличие нулевого символа.
	6) lpcbData Указатель на переменную, которая определяет размер буфера, принимающего данные из параметра, в байтах. После того, как функция вернет значение, эта переменная будет содержать размер данных, скопированных в буфер. Если данные носят текстовый характер (REG_xxx_SZ), то также включается и нулевой символ (нулевые символы для REG_MULTI_SZ). Если размер буфера, недостаточен для сохранения данных, то функция вернет ERROR_MORE_DATA и сохранит требуемый размер буфера в переменную, на которую указывает этот параметр. Если lpData - NULL, а параметр lpcbData не нулевой, функция возвращает ERROR_SUCCESS и сохраняет размер данных в переменной, на которую указывает lpcbData.

	Если функция выполнена успешно, возвращается ERROR_SUCCESS, в противном случае возвращается ненулевой код ошибки, определенный в Winerror.h
	Как видим, функция RegQueryValueEx предоставляет возможность программисту вначале проверить, каков размер данных в параметре, а затем уже его считать. Это позволяет выделять память динамически, по ходу выполнения программы.

	*/

	/*
	Функция устанавливает значение параметра.

	LONG RegSetValueEx(
	1)HKEY hKey,
	2) LPCTSTR lpValueName,
	3) DWORD Reserved,
	4) DWORD dwType,
	5) const BYTE* lpData,
	6) DWORD cbData)


	1) hKey Описатель открытого раздела. Раздел должен быть открыт с правами KEY_SET_VALUE.
	2) lpValueName Указатель на строку, которая содержит название параметра, значение которого нужно установить. Если параметра с таким именем не существует, функция создаст его. Если параметр равен NULL, или пустой строке, то устанавливается значение параметра по умолчанию. В Windows Me/98/95 каждый раздел имеет параметр по умолчанию, который первоначально не содержит данных. В Windows 95 по умолчанию тип этого параметра - REG_SZ.
	3) Reserved Зарезервировано - NULL.
	4) dwType Тип данных параметра.
	5) lpData Указатель на буфер, содержащий данные, которые должны быть сохранены в соответствующем параметре. Для строк, таких как REG_SZ, строка должна заканчиваться нулевым символом. Для типа REG_MULTI_SZ строка должна заканчиваться двумя нулевыми символами.
	6) cbData Размер буфера lpData, в байтах. Если данные имеют тип REG_SZ, REG_MULTI_SZ или REG_EXPAND_SZ, то параметр должен учитывать нулевой или нулевые символы.

	Если функция выполнена успешно, возвращается ERROR_SUCCESS, в противном случае возвращается ненулевой код ошибки, определенный в Winerror.h
	*/


	/*
	Функция закрывает дескриптор ключа рестра

	LONG RegCloseKey(
	1) HKEY hKey)

	1) hKey Описатель открытого раздела, который подлежит закрытию.
	Если описатель успешно освобожден, функция возвращает ERROR_SUCCESS, в противном случае вернет ненулевой код ошибки, определенный в Winerror.h
	*/

	HMENU subFileMenu = CreatePopupMenu();
	HKEY key;
	LONG Result;
	Result = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\БПВ-1321\\Registry", 0, 0, 0, KEY_ALL_ACCESS, 0, &key, 0);
	if (Result != ERROR_SUCCESS)
	{
		AppendMenu(subFileMenu, MF_STRING | MF_GRAYED, WM_USER, "(Пусто)");
	}
	else
	{
		DWORD len = MAX_PATH, len2 = sizeof(DWORD);
		char Name[10];
		DWORD size;
		Result = RegQueryValueEx(key, "Quantity", 0, 0, (BYTE*)&size, &len2);
		if (Result != ERROR_SUCCESS)
			AppendMenu(subFileMenu, MF_STRING | MF_GRAYED, WM_USER, "(Пусто)");
		else
		{
			for (int i = 0; i < size; i++)
			{
				char *PathName = new char[MAX_PATH];
				ZeroMemory(PathName, MAX_PATH);
				wsprintf(Name, "Path%d", i);
				Result = RegQueryValueEx(key, Name, 0, 0, (BYTE*)PathName, &len);
				if (Result == ERROR_SUCCESS)
				{
					if (!_access(PathName, 0))
					{
						pathes.push_back(PathName);
						char *p = strrchr(PathName, '\\');
						AppendMenu(subFileMenu, MF_STRING, WM_USER + i, p + 1);
					}

				}
				len = MAX_PATH;
			}
		}
	}
	HMENU mainMenu = CreateMenu();
	AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subFileMenu, "Recent Files");
	SetMenu(hDialog, mainMenu);
	RegCloseKey(key);
}