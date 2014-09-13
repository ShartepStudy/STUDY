#ifndef _CURSOR_H_
#define _CURSOR_H_
#include"const.h"

class CSeaFightApp;

class CCursor
{
public:
   CCursor( CSeaFightApp & host );
   ~CCursor();
public:
   void moveRight();
   void moveLeft();
   void moveUp();
   void moveDown();

   unsigned short getX();
   unsigned short getY();
private:
   //    кординаты курсора
   int x, y;

   CSeaFightApp & mHost;
};



inline unsigned short CCursor::getX()
{
   return x;
} 

inline unsigned short CCursor::getY()
{
   return y;
}

#endif

