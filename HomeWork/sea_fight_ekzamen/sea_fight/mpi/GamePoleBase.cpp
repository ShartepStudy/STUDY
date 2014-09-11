#include "GamePoleBase.h"
#include "SeaFightApp.h"


CGamePoleBase::CGamePoleBase( CSeaFightApp & host, COORD poleCoord ) :
   mHost( host ),
   mPoleCoord( poleCoord )
{
   for( int y = 0; y <= GAME_POLE_SIZE*2; y++ )
   {
      for( int x = 0; x <= GAME_POLE_SIZE*2; x++ )
      {
         if( !(x%2) && (y%2) )                                    setChar(x, y, 0x2502);
         else if( (x%2) && !(y%2) )                               setChar( x, y, 0x2500 );
         else if( !(x%2) && !(y%2) && x>0 && x<GAME_POLE_SIZE*2 && y>0 && y<GAME_POLE_SIZE*2 )
                                                                  setChar(x, y, 0x253C);
         else if( !x && !(y%2) && y>0 && y<GAME_POLE_SIZE*2 )     setChar( x, y, 0x251C );
         else if( x==GAME_POLE_SIZE*2 && !(y%2) && y>0 && y<GAME_POLE_SIZE*2 )
                                                                  setChar( x, y, 0x2524 );
         else if( !y && !(x%2) && x>0 && x<GAME_POLE_SIZE*2 )     setChar( x, y, 0x252C );
         else if( y==GAME_POLE_SIZE*2 && !(x%2) && x>0 && x<GAME_POLE_SIZE*2 )
                                                                  setChar( x, y, 0x2534 );
         else if( !x && !y )                                      setChar( x, y, 0x250C );
         else if( !x && y==GAME_POLE_SIZE*2 )                     setChar( x, y, 0x2514 );
         else if( x==GAME_POLE_SIZE*2 && !y )                     setChar( x, y, 0x2510 );
         else if( x==GAME_POLE_SIZE*2 && y==GAME_POLE_SIZE*2 )    setChar( x, y, 0x2518 );
         else                                                     setChar( x, y, EMPTY_NON_SHOOTED );
      }
   }
}

CGamePoleBase::~CGamePoleBase()
{}

void CGamePoleBase::setChar( int x, int y, wchar_t c )
{
   mHost.SetChar( mPoleCoord.X+x, mPoleCoord.Y+y, c );
}

bool CGamePoleBase::canSetShip( short x, short y, bool vertical, short size )
{
   if( vertical )
   {
      for( short j = y-1; j <= y+1; j++ )
      {
         for( short i = x-1; i <= x+size; i++ )
         {
            if( getValue( i, j )==SHIP_NON_SHOOTED ) return false;
         }
      }
   }
   else
      for( short j = y-1; j <= y+size; j++ )
      {
         for( short i = x-1; i <= x+1; i++ )
         {
            if( getValue( i, j )==SHIP_NON_SHOOTED ) return false;
         }
      }

   return true;
}

bool CGamePoleBase::isGameOver()
{
   for( size_t i = 0; i < GAME_POLE_SIZE; i++ )
   {
      for( size_t j = 0; j < GAME_POLE_SIZE; j++ )
      {
         if( getValue( j, i )==SHIP_NON_SHOOTED ) return false;
      }
   }
   return true;
}

bool CGamePoleBase::isShipKilled( short x, short y, EDirection direction )
{
   switch( direction )
   {
   case ALL:
      if( getValue( x-1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x+1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y-1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y+1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x-1, y )==SHIP_SHOOTED && !isShipKilled( x-1, y, LEFT ) ) return false;
      if( getValue( x+1, y )==SHIP_SHOOTED && !isShipKilled( x+1, y, RIGHT ) ) return false;
      if( getValue( x, y-1 )==SHIP_SHOOTED && !isShipKilled( x, y-1, UP ) ) return false;
      if( getValue( x, y+1 )==SHIP_SHOOTED && !isShipKilled( x, y+1, DOWN ) ) return false;
      break;

   case LEFT:
      if( getValue( x-1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y-1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y+1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x-1, y )==SHIP_SHOOTED && !isShipKilled( x-1, y, LEFT ) ) return false;
      if( getValue( x, y-1 )==SHIP_SHOOTED && !isShipKilled( x, y-1, UP ) ) return false;
      if( getValue( x, y+1 )==SHIP_SHOOTED && !isShipKilled( x, y+1, DOWN ) ) return false;
      break;

   case RIGHT:
      if( getValue( x+1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y-1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y+1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x+1, y )==SHIP_SHOOTED && !isShipKilled( x+1, y, RIGHT ) ) return false;
      if( getValue( x, y-1 )==SHIP_SHOOTED && !isShipKilled( x, y-1, UP ) ) return false;
      if( getValue( x, y+1 )==SHIP_SHOOTED && !isShipKilled( x, y+1, DOWN ) ) return false;
      break;

   case UP:
      if( getValue( x-1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x+1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y-1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x-1, y )==SHIP_SHOOTED && !isShipKilled( x-1, y, LEFT ) ) return false;
      if( getValue( x+1, y )==SHIP_SHOOTED && !isShipKilled( x+1, y, RIGHT ) ) return false;
      if( getValue( x, y-1 )==SHIP_SHOOTED && !isShipKilled( x, y-1, UP ) ) return false;
      break;

   case DOWN:
      if( getValue( x-1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x+1, y )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x, y+1 )==SHIP_NON_SHOOTED ) return false;
      if( getValue( x-1, y )==SHIP_SHOOTED && !isShipKilled( x-1, y, LEFT ) ) return false;
      if( getValue( x+1, y )==SHIP_SHOOTED && !isShipKilled( x+1, y, RIGHT ) ) return false;
      if( getValue( x, y+1 )==SHIP_SHOOTED && !isShipKilled( x, y+1, DOWN ) ) return false;
      break;
   }

   return true;
}

void CGamePoleBase::markKilledShip( short x, short y, EDirection direction )
{
   switch( direction )
   {
   case ALL:
      for( int j = y-1; j <= y+1; j++ )
         for( int i = x-1; i <= x+1; i++ )
            if( getValue( i, j )==EMPTY_NON_SHOOTED ) 
               setValue( i, j, EMPTY_SHOOTED );
      
      if( getValue( x-1, y )==SHIP_SHOOTED ) markKilledShip( x-1, y, LEFT );
      if( getValue( x+1, y )==SHIP_SHOOTED ) markKilledShip( x+1, y, RIGHT );
      if( getValue( x, y-1 )==SHIP_SHOOTED ) markKilledShip( x, y-1, UP );
      if( getValue( x, y+1 )==SHIP_SHOOTED ) markKilledShip( x, y+1, DOWN );
      break;

   case LEFT:
      for( int j = y-1; j <= y+1; j++ )
         for( int i = x-1; i <= x+1; i++ )
            if( getValue( i, j )==EMPTY_NON_SHOOTED ) 
               setValue( i, j, EMPTY_SHOOTED );

      if( getValue( x-1, y )==SHIP_SHOOTED ) markKilledShip( x-1, y, LEFT );
      if( getValue( x, y-1 )==SHIP_SHOOTED ) markKilledShip( x, y-1, UP );
      if( getValue( x, y+1 )==SHIP_SHOOTED ) markKilledShip( x, y+1, DOWN );
      break;

   case RIGHT:
      for( int j = y-1; j <= y+1; j++ )
         for( int i = x-1; i <= x+1; i++ )
            if( getValue( i, j )==EMPTY_NON_SHOOTED ) 
               setValue( i, j, EMPTY_SHOOTED );

      if( getValue( x+1, y )==SHIP_SHOOTED ) markKilledShip( x+1, y, RIGHT );
      if( getValue( x, y-1 )==SHIP_SHOOTED ) markKilledShip( x, y-1, UP );
      if( getValue( x, y+1 )==SHIP_SHOOTED ) markKilledShip( x, y+1, DOWN );
      break;

   case UP:
      for( int j = y-1; j <= y+1; j++ )
         for( int i = x-1; i <= x+1; i++ )
            if( getValue( i, j )==EMPTY_NON_SHOOTED ) 
               setValue( i, j, EMPTY_SHOOTED );

      if( getValue( x-1, y )==SHIP_SHOOTED ) markKilledShip( x-1, y, LEFT );
      if( getValue( x+1, y )==SHIP_SHOOTED ) markKilledShip( x+1, y, RIGHT );
      if( getValue( x, y-1 )==SHIP_SHOOTED ) markKilledShip( x, y-1, UP );
      break;

   case DOWN:
      for( int j = y-1; j <= y+1; j++ )
         for( int i = x-1; i <= x+1; i++ )
            if( getValue( i, j )==EMPTY_NON_SHOOTED ) 
               setValue( i, j, EMPTY_SHOOTED );

      if( getValue( x-1, y )==SHIP_SHOOTED ) markKilledShip( x-1, y, LEFT );
      if( getValue( x+1, y )==SHIP_SHOOTED ) markKilledShip( x+1, y, RIGHT );
      if( getValue( x, y+1 )==SHIP_SHOOTED ) markKilledShip( x, y+1, DOWN );
      break;
   }
}

char CGamePoleBase::shoot( int x, int y )
{
   short value = getValue( x, y );
   if( value==EMPTY_NON_SHOOTED )
   {
      setValue( x, y, EMPTY_SHOOTED );
      return FAIL_SHOOT;
   }
   else if( value==SHIP_NON_SHOOTED )
   {
      setValue( x, y, SHIP_SHOOTED );
      if( isShipKilled( x, y ) )
      {
         markKilledShip( x, y );
         return KILLED_SHOOT;
      }
      return HURT_SHOOT;
   }
   return ERROR_SHOOT;
}