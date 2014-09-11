#ifndef _GAME_POLE_BASE_H_
#define _GAME_POLE_BASE_H_

#include "const.h"
#include <Windows.h>

class CSeaFightApp;

class CGamePoleBase
{
public:
   CGamePoleBase( CSeaFightApp & host, COORD poleCoord );
   ~CGamePoleBase();

public:
   void setChar( int x, int y, wchar_t c );
   bool isGameOver();
   virtual void setValue( int x, int y, char v ) = 0;
   virtual char getValue( int x, int y ) = 0;
   char shoot( int x, int y );

protected:
   bool canSetShip( short x, short y, bool vertical, short size );
   bool isShipKilled( short x, short y, EDirection direction = ALL );
   void markKilledShip( short x, short y, EDirection direction = ALL );

protected:
   CSeaFightApp & mHost;
   COORD mPoleCoord;
};

#endif
