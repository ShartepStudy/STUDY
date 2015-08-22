#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	HMODULE hMod = LoadLibrary(L"shared_section_dll.dll");

	auto p_getAlex = (int(*)())GetProcAddress(hMod, "getAlex");
	int alex_age = p_getAlex();

	cout << "Alex age: " << alex_age << "\n";
	cout << "Set new value: "; cin >> alex_age;

	auto p_setAlex = (void(*)(int))GetProcAddress(hMod, "setAlex");
	p_setAlex(alex_age);

	alex_age = p_getAlex();
	cout << "Now, " << alex_age << "\n";

	cout << "Please, start another instance!\n";
	Sleep(60000);
}