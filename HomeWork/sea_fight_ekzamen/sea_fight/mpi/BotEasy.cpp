#include "BotEasy.h"
#include "GamePolePlayer.h"


CBotEasy::CBotEasy( CGamePolePlayer & playerPole ) :
   IBot(),
   mPlayerPole( playerPole ),
   mHurt( false )
{}

CBotEasy::~CBotEasy()
{}

void CBotEasy::execute()
{
   char shoot;
   
   // �������� �������� ��������, �.�. � ���������� �������� ������ ���������
   // ��� �������� ��� ��������
   if( !mHurt )               
   {
      do
      {
         mCoord1.X = rand()%10;
         mCoord1.Y = rand()%10;
      }
      while( !(shoot = mPlayerPole.shoot( mCoord1.X, mCoord1.Y )) );
      
      if( shoot==HURT_SHOOT )
      {
         mHurt++;
         mDirect = RIGHT_DIRECT;
         mCoord2 = mCoord1;
      }
   }
   
   
   // �������� �������� ����� ������� ���������, ���������� ��������������� �������� 
   // �� ���� ��������� �������� �������, ��� ��������� � �������� ��������� � ���������� ��������� �2
   // � ������ ���� ��� �������� ������ ���������, � �������� �� ����, �� ��������� � ��������� �3
   else if( mHurt==1 )
   {
      do
      {
         COORD c = mCoord2;
         switch( mDirect )
         {
         case RIGHT_DIRECT: c.X++; break;
         case DOWN_DIRECT: c.Y++; break;
         case LEFT_DIRECT: c.X--; break;
         case UP_DIRECT: c.Y--; break;
         }

         shoot = mPlayerPole.shoot( c.X, c.Y );

         if( shoot==KILLED_SHOOT ) mHurt = 0;
         else if( shoot==ERROR_SHOOT ) mDirect++;
         else if( shoot==FAIL_SHOOT ) 
         {
            if( mDirect==UP_DIRECT ) mHurt = 3;
            else mDirect++; 
         }
         else if( shoot==HURT_SHOOT )
         {
            mCoord2 = c;
            mHurt = 2;
         }
      }
      while( shoot==ERROR_SHOOT );
   }

   // �������� �������� ����� ������� ���������, ��� �������� ����������� �������, ������� 
   // ���������� �������� � ���� ����������� ���� �������� �� ����� ���� ���� � ���� ����������� 
   // ��������� ������ ��� ��� ������������ ������, ����� ��������� � ��������� �3
   else if( mHurt==2 )
   {
      COORD c = mCoord2;
      switch( mDirect )
      {
      case RIGHT_DIRECT: c.X++; break;
      case DOWN_DIRECT: c.Y++; break;
      case LEFT_DIRECT: c.X--; break;
      case UP_DIRECT: c.Y--; break;
      }

      shoot = mPlayerPole.shoot( c.X, c.Y );

      if( shoot==KILLED_SHOOT ) mHurt = 0;
      else if( shoot==ERROR_SHOOT || shoot==FAIL_SHOOT ) mHurt = 3;
      else if( shoot==HURT_SHOOT ) mCoord2 = c;
   }

   // �������� �������� ����� ���� ��� ������ ��� ������ � ��������� �����������,
   // ���������� �������� � ��������������� ����������� ������� � ������ � ������� ������
   // � ������ ���, ���� ����� ����� �������� �������� �� ���� ��������� � ��������� �2
   else if( mHurt==3 )
   {
      COORD c = mCoord1;

      if( mDirect==RIGHT_DIRECT ) mDirect=LEFT_DIRECT;
      else if( mDirect==LEFT_DIRECT ) mDirect=RIGHT_DIRECT;
      else if( mDirect==UP_DIRECT ) mDirect=DOWN_DIRECT;
      else if( mDirect==DOWN_DIRECT ) mDirect=UP_DIRECT;

      switch( mDirect )
      {
      case RIGHT_DIRECT: c.X++; break;
      case DOWN_DIRECT: c.Y++; break;
      case LEFT_DIRECT: c.X--; break;
      case UP_DIRECT: c.Y--; break;
      }

      shoot = mPlayerPole.shoot( c.X, c.Y );

      if( shoot==KILLED_SHOOT ) mHurt = 0;
      else if( shoot==HURT_SHOOT )
      {
         mCoord2 = c;
         mHurt = 2;
      }

   }
}