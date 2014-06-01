#include <iostream>
using namespace std;

class CPoint
{
private:
   float mX;
   float mY;

public:
   CPoint() 
      : mX( 0 )
      , mY( 0 ) 
   {}
   CPoint( float x, float y ) 
      : mX( x )
      , mY( y ) 
   {}

   float getX() 
   { 
      return mX; 
   }
   float getY() 
   { 
      return mY; 
   }

   void setX( float x ) 
   { 
      mX = x; 
   }
   void setY( float y ) 
   { 
      mY = y; 
   }

   void moveUp( float offset ) 
   { 
      mY += offset; 
   }
   void moveDown( float offset ) 
   { 
      mY -= offset; 
   }
   void moveLeft( float offset )    
   { 
      mX -= offset; 
   }
   void moveRight( float offset ) 
   { 
      mX += offset; 
   }

   void showCordinatesOnConsole()
   {
      cout << "x=" << mX << " y=" << mY << endl;
   }

   ~CPoint() {};
};

void main() 
{
   CPoint A;
   CPoint B(5, 7);

   A.showCordinatesOnConsole();
   B.showCordinatesOnConsole();

   A.moveDown( 5 );
   B.moveLeft( 10 );

   A.showCordinatesOnConsole();
   B.showCordinatesOnConsole();

   A.moveUp( 20 );
   B.moveRight( 30 );

   A.showCordinatesOnConsole();
   B.showCordinatesOnConsole();
   
}
