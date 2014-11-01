#define __CLOCK__
#include "clock.h"

Clock::Clock()
{
	hour = sec = min = 0;
}

Clock::Clock(UINT h, UINT m, UINT s)
{
	SetTime(h, m, s);
}

void Clock::SetTime(UINT h, UINT m, UINT s)
{
	hour = h % 24;
	min = m % 60;
	sec = s % 60;
}

LPSTR Clock::Tick()
{
	static CHAR strtime[15];
	wsprintf(strtime, "%02d : %02d : %02d", hour, min, sec);
	++sec;
	if(sec == 60)
	{
		sec = 0;
		++min;
		if (min == 60)
		{
			min = 0;
			++hour;
		}
		if (hour == 24)
			hour = 0;
	}
	return strtime;
}