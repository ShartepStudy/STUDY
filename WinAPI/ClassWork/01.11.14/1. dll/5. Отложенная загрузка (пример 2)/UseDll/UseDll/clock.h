
#include "windows.h"
#ifndef __CLOCK__
#define _MYDLL_ __declspec(dllimport)
#else
#define _MYDLL_ __declspec(dllexport)
#endif

class _MYDLL_ Clock
{
	UINT hour,min,sec;
public:
	Clock();
	Clock(UINT,UINT,UINT);
	LPSTR Tick();
	void SetTime(UINT,UINT,UINT);
};