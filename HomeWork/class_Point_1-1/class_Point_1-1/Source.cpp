#include <iostream>
#include "C_Point.h"
using namespace std;

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
