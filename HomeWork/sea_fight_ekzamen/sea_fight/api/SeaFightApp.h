#ifndef _SEA_FIGHT_APP_H_
#define _SEA_FIGHT_APP_H_

#include "BaseApp.h"
#include "Cursor.h"
#include "GamePoleComp.h"
#include "GamePolePlayer.h"
#include "IBot.h"
#include "BotVeryEasy.h"
#include "BotEasy.h"
#include "const.h"

#include <time.h>
#include <conio.h>

class CSeaFightApp : public BaseApp
{
public:
   CSeaFightApp();
   ~CSeaFightApp();

public:
   virtual void KeyPressed( int btnCode );
	virtual void UpdateF(float deltaTime);

public:

private:
   // метод проверяет не наступил ли конец игры 
   void checkGameOver();

public:
   CGamePoleComp mCompPole;
   CGamePolePlayer mPlayerPole;

private:
   CCursor mCursor;
   IBot * mBot;

   float mDeltaTime;
   bool mNowComputerHod;
};

#endif