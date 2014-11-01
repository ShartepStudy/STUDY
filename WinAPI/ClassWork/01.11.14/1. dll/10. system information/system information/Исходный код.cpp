#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/*
Каждому процессу операционная система выделяет собственное виртуальное адресное пространство.
В Win32 его размер составляет 4 Гбайт, что определяется разрядностью регистра команд.
Соответственно, 32-битный указатель может быть любым числом в интервале от 0x00000000 до OxFFFFFFFF.
Таким образом, адресуется 4 294 967 296 значений, что как раз и перекрывает указанный диапазон памяти.

Структура виртуального адресного пространства для операционной системы Windows2000/XP.

Диапазоны:
1) 0x00000000 : 0x0000FFFF – данный сегмент предназначен для так называемых нулевых указателей,
при обращении по одному из этих адресов генерируется исключение и приложение будет закрыто.

2) 0x0001000 : 0x7FFEFFFF – диапазон предназначен для кода и пользовательских данных.
Данный диапазон адресов закрыт, т.е. сюда не могут обратиться другие процессы.
В этот диапазон адресов загружаются dll-модули.

3) 0x7FFF0000 : 0x7FFFFFFF – данный диапазон адресов является закрытым и предназначен для простоты
внутренней реализации операционной системы.

4) 0x80000000 : 0xFFFFFFFF -  данный диапазон предназначен для кода и данных режима ядра
(код операционной системы, мютексы, семафоры, драйверы устройств, код низкоуровневого управления потоками,
памятью, файловой системой, сетевой поддержкой). Этот раздел полностью защищен,
т.е. обращение под одному из адресов этого раздела вызовет нарушение доступа и приложение будет закрыто.

Из 4 Гб виртуального адресного  пространства процессу доступно только 2Гб, другие 2Гб использует ОС.
Виртуальная память = оперативная память + файл подкачки;
Подкачка – перемещение данных из оперативной памяти в файл и обратно.

Диспетчер виртуальной памяти (Virtual Memory Manager — VMM) является составной частью ядра операционной системы.
Он отображает виртуальные адреса на физические, используя механизм подкачки страниц памяти.

void GetSystemInfo( - получает информацию о системе
LPSYSTEM_INFO lpSystemInfo - указатель на структуру SYSTEM_INFO
);

typedef struct _SYSTEM_INFO {
union {
DWORD dwOemId; // не используется
struct {
WORD wProcessorArchitecture; - архитектура процессора
PROCESSOR_ARCHITECTURE_UNKNOWN – архитектура неизвестна
PROCESSOR_ARCHITECTURE_INTEL – архитектура INTEL
WORD wReserved;
};
};
DWORD dwPageSize; - размер страницы
LPVOID lpMinimumApplicationAddress; - минимальный адрес памяти доступного адресного пространства.
LPVOID lpMaximumApplicationAddress; - максимальный адрес памяти доступного адресного пространства.
DWORD_PTR dwActiveProcessorMask; - битовая маска, которая показывает какие процессоры сейчас активны.
DWORD dwNumberOfProcessors; - количество процессоров в системе
DWORD dwProcessorType; - тип процессора
DWORD dwAllocationGranularity; - гранулярность
WORD wProcessorLevel; - дополнительные подробности об архитектуре процессора (например Intel Pentium Pro или Pentium II ).
WORD wProcessorRevision; - дополнительные подробности об уровне данной архитектуры процессора (номер модели)
} SYSTEM_INFO;

void GlobalMemoryStatus(
LPMEMORYSTATUS lpBuffer - указатель на структуру MEMORYSTATUS
);

typedef struct _MEMORYSTATUS {
DWORD dwLength; // размер структуры в байтах
DWORD dwMemoryLoad; // на сколько занята подсистема управления памятью 0 - 100 (0 – память полностью свободна, 100 – память полностью загружена)
DWORD dwTotalPhys; // общий объем физической (оперативной) памяти в байтах
DWORD dwAvailPhys; // общее число байт свободной физической памяти
DWORD dwTotalPageFile; // максимальное количество байтов, которое может содержаться в страничном файле
DWORD dwAvailPageFile; // свободный объем в страничном файле
DWORD dwTotalVirtual; // общий объем виртуального адресного пространства
DWORD dwAvailVirtual; // свободный объем виртуального адресного пространства
} MEMORYSTATUS, *LPMEMORYSTATUS;
*/

void main()
{
	setlocale(0, "");

	SYSTEM_INFO s;
	GetSystemInfo(&s);
	string str = "Архитектура процессора: ";
	switch (s.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		str += "Intel\n";
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		str += "x64 (AMD or Intel)\n";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		str += "Intel Itanium Processor Family (IPF)\n";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		str += "Неизвестная архитектура\n";
		break;
	}
	str += "Тип процессора: ";
	switch (s.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
		str += "INTEL_386\n";
		break;
	case PROCESSOR_INTEL_486:
		str += "INTEL_486\n";
		break;
	case PROCESSOR_INTEL_PENTIUM:
		str += "INTEL_PENTIUM\n";
		break;
	case PROCESSOR_INTEL_IA64:
		str += "INTEL_IA64\n";
		break;
	case PROCESSOR_AMD_X8664:
		str += "AMD_X8664\n";
		break;
	}
	str += "Уровень процессора: ";
	switch (s.wProcessorLevel)
	{
	case 3:
		str += "Intel 80386\n";
		break;
	case 4:
		str += "Intel 80486\n";
		break;
	case 5:
		str += "Intel Pentium\n";
		break;
	case 6:
		str += "Intel Pentium II\n";
		break;
	}
	str += "Минимальный адрес памяти: ";
	char buf[15];
	wsprintfA(buf, "%x\n", s.lpMinimumApplicationAddress);
	str += buf;
	str += "Максимальный адрес памяти: ";
	wsprintfA(buf, "%x\n", s.lpMaximumApplicationAddress);
	str += buf;
	str += "Число процессоров: ";
	wsprintfA(buf, "%u\n", s.dwNumberOfProcessors);
	str += buf;

	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);

	str += "\nОбщий объем физической памяти в килобайтах: ";
	wsprintfA(buf, "%u\n", ms.dwTotalPhys / 1024);
	str += buf;
	str += "Общий объем свободной физической памяти в килобайтах: ";
	wsprintfA(buf, "%u\n", ms.dwAvailPhys / 1024);
	str += buf;
	str += "Общий объем виртуального адресного пространства: ";
	wsprintfA(buf, "%u\n", ms.dwTotalVirtual / 1024);
	str += buf;
	str += "Свободный объем виртуального адресного пространства: ";
	wsprintfA(buf, "%u\n", ms.dwAvailVirtual / 1024);
	str += buf;
	cout << str << "\n";
}
