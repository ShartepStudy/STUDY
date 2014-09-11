#ifndef _CBOT_EASY_H_
#define _CBOT_EASY_H_

#include "IBot.h"
#include <Windows.h>
using namespace std;

class CGamePolePlayer;

class CBotEasy : public IBot
{
public:
   CBotEasy( CGamePolePlayer & playerPole );
   ~CBotEasy();

public:
   virtual void execute();

private:
   CGamePolePlayer & mPlayerPole;
   char mHurt;
   COORD mCoord1;
   COORD mCoord2;
   char mDirect;
};

#endif

