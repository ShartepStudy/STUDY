
#include <windows.h>
#include "resource.h"

#include <delayimp.h>
#include "implicit linking.h"
#pragma comment (lib, "Delayimp.lib") // ����������� lib ����� ��� ���������� ��������
#pragma comment (lib, "implicit_linking.lib")

/*

���������� �������� (Delay Loaded DLL) ���������� ������������ � �����, � ������� ��������. 
���������� ����������� ��������� DLL ������ ����� ��� ���������� � ��������� �� �������.
��� ������������� ���������� �������� ���������� ����������� DLL � LIB ���� ��� ��������� delayimp.lib � delayimp.dll. 
��� ����������� ���������������� DLL ����������:
Properties->Linker->Input->Delay Loaded dll (implicit_linking.dll)

��� �������� �� ������ dll ����������:
1. ���������� ���� #include "delayimp.h"
2. Properties->Linker->Advanced->Delay Loaded Dll (Support Unload (/DELAY:UNLOAD))

*/
