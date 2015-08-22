
#ifdef __MYDLL__
#define SIMPLE_EXAMPLE extern "C" __declspec(dllexport)
#else
#define SIMPLE_EXAMPLE extern "C" __declspec(dllimport)
#endif

SIMPLE_EXAMPLE void MessageInfo(char* str);
SIMPLE_EXAMPLE void Ref(int& ref);
SIMPLE_EXAMPLE int counter;

/*
DLL - ����������� ������������ ����������. 
������ ���� �����: 
1) ������ �������, ����������, ���������, ������ � �.�.
2) ������ �������.
User32.dll � ������� ����������������� ���������� � ������� �������� ���������.
Kernell.dll � ������� ��� ���������� �������, �������� � ����������.
Gdi32.dll � ������� ��� ������ ������� � ������.
Cards.dll � ������ ������� (�����).

�������� dll ������������� ��������� �����������: 
1)	������� ���������� ������� � �������;
2)	�������� �������� ������������ ���� ����� ���������;
3)	����������� ������������� ���������� ������ ����������������;
4)	�������� ������ � dll ���� ��� ����������� � ����������� ������ � ����� ����� �������������� ������� ������������;
5)	���������� ���������������� ����������;
6)	���������� ��������.

������� ���������� dll:
1)	������� ����������;
2)	����� ����������;
3)  ���������� ��������.

__declspec (decline specification) � ����� ����������� �������� ����������� ��� ����������� �������������� �������.
dllexport � ������� � ���, ��� ������� ��������������
dllimport � ������� � ���, ��� ������� �������������
extern "C" � ������� ����������� � ���, ��� �� ����� ����������� ������������� �����, �.�. �������� ���.

*/