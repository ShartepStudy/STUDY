#include "GamePolePlayer.h"
#include "SeaFightApp.h"

CGamePolePlayer::CGamePolePlayer( CSeaFightApp & host ) :
   CGamePoleBase( host, { GAME_POLE_INTERVAL, GAME_POLE_INTERVAL } )
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

CGamePolePlayer::~CGamePolePlayer()
{}

void CGamePolePlayer::setShips()    /*************************/
{
   short x, y;
   bool vertical;

   for( size_t size = BIGGEST_SHIP_SIZE; size > 0; size-- )
   {
      for( size_t j = 0; j <= BIGGEST_SHIP_SIZE-size; j++ )
      {
         do
         {
            vertical = rand()%2;
            if( vertical )
            {
               x = rand() % (GAME_POLE_SIZE+1-size);
               y = rand() % 10;
            }
            else
            {
               x = rand() % 10;
               y = rand() % (GAME_POLE_SIZE+1-size);
            }
         }
         while( !canSetShip( x, y, vertical, size ) );

         if( vertical )
         {
            for( size_t i = 0; i < size; i++ )
            {
               setValue( x+i, y, SHIP_NON_SHOOTED );
            }
         }
         else
         {
            for( size_t i = 0; i < size; i++ )
            {
               setValue( x, y+i, SHIP_NON_SHOOTED );
            }
         }
      }
   }
}

void CGamePolePlayer::setValue( int x, int y, char v )
{
   if( x<0 || x>=GAME_POLE_SIZE || y<0 || y>=GAME_POLE_SIZE ) return;
   switch( v )
   {
   case EMPTY_SHOOTED: setChar( x*2+1, y*2+1, EMPTY_SHOOTED_CHAR ); break;
   case SHIP_NON_SHOOTED: setChar( x*2+1, y*2+1, PLAYER_SHIP_NON_SHOOTED_CHAR ); break;
   case SHIP_SHOOTED: setChar( x*2+1, y*2+1, SHIP_SHOOTED_CHAR ); break;
   }   
}

char CGamePolePlayer::getValue( int x, int y )
{
   if( x<0 || x>=GAME_POLE_SIZE || y<0 || y>=GAME_POLE_SIZE ) return STATE_NON_DEFINE;
   switch( mHost.GetChar( mPoleCoord.X + x*2 + 1, mPoleCoord.Y + y*2 + 1 ) )
   {
   case EMPTY_SHOOTED_CHAR: return EMPTY_SHOOTED;              //    в эту €чейку уже стрел€ли и она пуста€
   case PLAYER_SHIP_NON_SHOOTED_CHAR: return SHIP_NON_SHOOTED;   //    в этой €чейке спр€тан корабль
   case SHIP_SHOOTED_CHAR: return SHIP_SHOOTED;                //    в этой €чейке подбитый корабль
   }
   return EMPTY_NON_SHOOTED;                                   //    пуста€ €чейка в которую еще не стрел€ли
}
