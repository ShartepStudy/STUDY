#ifndef _CBOT_VERY_EASY_H_
#define _CBOT_VERY_EASY_H_

#include "IBot.h"

class CGamePolePlayer;

class CBotVeryEasy : public IBot
{
public:
   CBotVeryEasy( CGamePolePlayer & playerPole );
   ~CBotVeryEasy();

public:
   virtual void execute();

private:
   CGamePolePlayer & mPlayerPole;
};

#endif

