#include "BotVeryEasy.h"
#include "GamePolePlayer.h"

CBotVeryEasy::CBotVeryEasy( CGamePolePlayer & playerPole ) :
   IBot(),
   mPlayerPole( playerPole )
{}

CBotVeryEasy::~CBotVeryEasy()
{}

void CBotVeryEasy::execute()
{
   int x, y;

   do
   {
      x = rand()%10;
      y = rand()%10;
   }
   while( !mPlayerPole.shoot( x, y ) );
}