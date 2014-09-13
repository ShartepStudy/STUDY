#include "Cursor.h"
#include "SeaFightApp.h"


CCursor::CCursor( CSeaFightApp & host ) : mHost( host ), x( 0 ), y( 0 )
{
   mHost.mCompPole.setChar( x*2+1, y*2, 0x2550 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2550 );
}


CCursor::~CCursor()
{}

void CCursor::moveRight()
{
   mHost.mCompPole.setChar( x*2+1, y*2, 0x2500 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2500 );
  
   if( x<GAME_POLE_SIZE-1 ) x++;
   else x = 0;

   mHost.mCompPole.setChar( x*2+1, y*2, 0x2550 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2550 );
}

void CCursor::moveLeft()
{
   mHost.mCompPole.setChar( x*2+1, y*2, 0x2500 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2500 );

   if( x>0 ) x--;
   else x = GAME_POLE_SIZE-1;

   mHost.mCompPole.setChar( x*2+1, y*2, 0x2550 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2550 );
}

void CCursor::moveDown()
{
   mHost.mCompPole.setChar( x*2+1, y*2, 0x2500 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2500 );
   if( y<GAME_POLE_SIZE-1 ) y++;
   else y = 0;
   mHost.mCompPole.setChar( x*2+1, y*2, 0x2550 );
   mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2550 );
}

void CCursor::moveUp()
{
      mHost.mCompPole.setChar( x*2+1, y*2, 0x2500 );
      mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2500 );
      if( y>0 ) y--;
      else y = GAME_POLE_SIZE-1;
      mHost.mCompPole.setChar( x*2+1, y*2, 0x2550 );
      mHost.mCompPole.setChar( x*2+1, y*2+2, 0x2550 );
}