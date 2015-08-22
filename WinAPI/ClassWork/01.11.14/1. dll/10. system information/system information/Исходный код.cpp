#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/*
������� �������� ������������ ������� �������� ����������� ����������� �������� ������������.
� Win32 ��� ������ ���������� 4 �����, ��� ������������ ������������ �������� ������.
��������������, 32-������ ��������� ����� ���� ����� ������ � ��������� �� 0x00000000 �� OxFFFFFFFF.
����� �������, ���������� 4 294 967 296 ��������, ��� ��� ��� � ����������� ��������� �������� ������.

��������� ������������ ��������� ������������ ��� ������������ ������� Windows2000/XP.

���������:
1) 0x00000000 : 0x0000FFFF � ������ ������� ������������ ��� ��� ���������� ������� ����������,
��� ��������� �� ������ �� ���� ������� ������������ ���������� � ���������� ����� �������.

2) 0x0001000 : 0x7FFEFFFF � �������� ������������ ��� ���� � ���������������� ������.
������ �������� ������� ������, �.�. ���� �� ����� ���������� ������ ��������.
� ���� �������� ������� ����������� dll-������.

3) 0x7FFF0000 : 0x7FFFFFFF � ������ �������� ������� �������� �������� � ������������ ��� ��������
���������� ���������� ������������ �������.

4) 0x80000000 : 0xFFFFFFFF -  ������ �������� ������������ ��� ���� � ������ ������ ����
(��� ������������ �������, �������, ��������, �������� ���������, ��� ��������������� ���������� ��������,
�������, �������� ��������, ������� ����������). ���� ������ ��������� �������,
�.�. ��������� ��� ������ �� ������� ����� ������� ������� ��������� ������� � ���������� ����� �������.

�� 4 �� ������������ ���������  ������������ �������� �������� ������ 2��, ������ 2�� ���������� ��.
����������� ������ = ����������� ������ + ���� ��������;
�������� � ����������� ������ �� ����������� ������ � ���� � �������.

��������� ����������� ������ (Virtual Memory Manager � VMM) �������� ��������� ������ ���� ������������ �������.
�� ���������� ����������� ������ �� ����������, ��������� �������� �������� ������� ������.

void GetSystemInfo( - �������� ���������� � �������
LPSYSTEM_INFO lpSystemInfo - ��������� �� ��������� SYSTEM_INFO
);

typedef struct _SYSTEM_INFO {
union {
DWORD dwOemId; // �� ������������
struct {
WORD wProcessorArchitecture; - ����������� ����������
PROCESSOR_ARCHITECTURE_UNKNOWN � ����������� ����������
PROCESSOR_ARCHITECTURE_INTEL � ����������� INTEL
WORD wReserved;
};
};
DWORD dwPageSize; - ������ ��������
LPVOID lpMinimumApplicationAddress; - ����������� ����� ������ ���������� ��������� ������������.
LPVOID lpMaximumApplicationAddress; - ������������ ����� ������ ���������� ��������� ������������.
DWORD_PTR dwActiveProcessorMask; - ������� �����, ������� ���������� ����� ���������� ������ �������.
DWORD dwNumberOfProcessors; - ���������� ����������� � �������
DWORD dwProcessorType; - ��� ����������
DWORD dwAllocationGranularity; - �������������
WORD wProcessorLevel; - �������������� ����������� �� ����������� ���������� (�������� Intel Pentium Pro ��� Pentium II ).
WORD wProcessorRevision; - �������������� ����������� �� ������ ������ ����������� ���������� (����� ������)
} SYSTEM_INFO;

void GlobalMemoryStatus(
LPMEMORYSTATUS lpBuffer - ��������� �� ��������� MEMORYSTATUS
);

typedef struct _MEMORYSTATUS {
DWORD dwLength; // ������ ��������� � ������
DWORD dwMemoryLoad; // �� ������� ������ ���������� ���������� ������� 0 - 100 (0 � ������ ��������� ��������, 100 � ������ ��������� ���������)
DWORD dwTotalPhys; // ����� ����� ���������� (�����������) ������ � ������
DWORD dwAvailPhys; // ����� ����� ���� ��������� ���������� ������
DWORD dwTotalPageFile; // ������������ ���������� ������, ������� ����� ����������� � ���������� �����
DWORD dwAvailPageFile; // ��������� ����� � ���������� �����
DWORD dwTotalVirtual; // ����� ����� ������������ ��������� ������������
DWORD dwAvailVirtual; // ��������� ����� ������������ ��������� ������������
} MEMORYSTATUS, *LPMEMORYSTATUS;
*/

void main()
{
	setlocale(0, "");

	SYSTEM_INFO s;
	GetSystemInfo(&s);
	string str = "����������� ����������: ";
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
		str += "����������� �����������\n";
		break;
	}
	str += "��� ����������: ";
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
	str += "������� ����������: ";
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
	str += "����������� ����� ������: ";
	char buf[15];
	wsprintfA(buf, "%x\n", s.lpMinimumApplicationAddress);
	str += buf;
	str += "������������ ����� ������: ";
	wsprintfA(buf, "%x\n", s.lpMaximumApplicationAddress);
	str += buf;
	str += "����� �����������: ";
	wsprintfA(buf, "%u\n", s.dwNumberOfProcessors);
	str += buf;

	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);

	str += "\n����� ����� ���������� ������ � ����������: ";
	wsprintfA(buf, "%u\n", ms.dwTotalPhys / 1024);
	str += buf;
	str += "����� ����� ��������� ���������� ������ � ����������: ";
	wsprintfA(buf, "%u\n", ms.dwAvailPhys / 1024);
	str += buf;
	str += "����� ����� ������������ ��������� ������������: ";
	wsprintfA(buf, "%u\n", ms.dwTotalVirtual / 1024);
	str += buf;
	str += "��������� ����� ������������ ��������� ������������: ";
	wsprintfA(buf, "%u\n", ms.dwAvailVirtual / 1024);
	str += buf;
	cout << str << "\n";
}
