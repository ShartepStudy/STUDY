#include <Windows.h>

///////////////////////////////////////////////

#pragma data_seg(".my_shared_section")
int Alex = 25;
char* message = new char[256];
#pragma data_seg()

#pragma comment (linker, "/SECTION:.my_shared_section,RWS")

///////////////////////////////////////////////

extern "C" __declspec(dllexport) int getAlex()
{
	return Alex;
}

extern "C" __declspec(dllexport) void setAlex(int x)
{
	Alex = x;
}

extern "C" __declspec(dllexport) const char* getMess()
{
	return message;
}

extern "C" __declspec(dllexport) void setMess(char* m)
{
	delete[]message;
	message = new char[lstrlenA(m) + 1];
	lstrcpyA(message, m);
}
