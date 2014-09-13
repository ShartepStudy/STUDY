#ifndef _GAME_POLE_COMP_H_
#define _GAME_POLE_COMP_H_

#include "GamePoleBase.h"

class CGamePoleComp : public CGamePoleBase
{
public:
   CGamePoleComp( CSeaFightApp & host );
   ~CGamePoleComp();

public:
   void setShips( );
   virtual void setValue( int x, int y, char v );
   virtual char getValue( int x, int y );

private:

private:

};

#endif
