#ifndef _GAME_POLE_PLAYER_H_
#define _GAME_POLE_PLAYER_H_

#include "GamePoleBase.h"

class CGamePolePlayer : public CGamePoleBase
{
public:
   CGamePolePlayer( CSeaFightApp & host );
   ~CGamePolePlayer();

public:
   void setShips( );
   virtual void setValue( int x, int y, char v );
   virtual char getValue( int x, int y );

private:

private:

};

#endif
