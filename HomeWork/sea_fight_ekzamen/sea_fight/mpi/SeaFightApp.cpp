#include"SeaFightApp.h"

CSeaFightApp::CSeaFightApp() :
   BaseApp( GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT ),
   mPlayerPole( *this ),
   mCompPole( *this ),
   mCursor( *this ),
   mDeltaTime(0),
   mNowComputerHod(false) ,
   mBot( new CBotEasy( mPlayerPole ) )
{
   srand( (int) time( NULL ) );
   mCompPole.setShips( );
   mPlayerPole.setShips( );
}

CSeaFightApp::~CSeaFightApp()
{
   delete mBot;
}

void CSeaFightApp::KeyPressed( int btnCode )
{
   if( !mNowComputerHod )
   {
      if( btnCode == 224 )
         btnCode = getch();
      switch( btnCode )
      {
      case 72:
         mCursor.moveUp();
         break;
      case 80:
         mCursor.moveDown();
         break;
      case 75:
         mCursor.moveLeft();
         break;
      case 77:
         mCursor.moveRight();
         break;
      case 32:
         if( mCompPole.shoot( mCursor.getX(), mCursor.getY() ) == FAIL_SHOOT ) 
            mNowComputerHod = !mNowComputerHod;
         break;
      }
   }
}

void CSeaFightApp::UpdateF( float deltaTime )
{
   mDeltaTime += deltaTime;
   if( mDeltaTime > GAME_DELAY )
   {
      if( mCompPole.isGameOver() )
      {
         cout << endl << endl << endl << "\t\tPlayer Win!!!   Game Over!!!";
         for( size_t i = 0; i < 30; i++ ) cout << endl;
         exit( 0 );
      }

      if( mPlayerPole.isGameOver() )
      {
         cout << endl << endl << endl << "\t\tComputer Win!!!   Game Over!!!";
         for( size_t i = 0; i < 30; i++ ) cout << endl;
         exit( 0 );
      }

      if( mNowComputerHod )
      {
         mBot->execute();

         mNowComputerHod = !mNowComputerHod;
      }

      mDeltaTime = 0;
   }
}

void CSeaFightApp::checkGameOver()
{
   
}
