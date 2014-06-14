#pragma once
#include <iostream>
using namespace std;

class CPoint
{
private:
   float mX;
   float mY;
public:
   CPoint();
   CPoint(float x, float y);
   ~CPoint();

   float getX();
   float getY();

   void setX(float x);
   void setY(float y);

   void moveUp(float offset);
   void moveDown(float offset);
   void moveLeft(float offset);
   void moveRight(float offset);
   
   void showCordinatesOnConsole();

};

