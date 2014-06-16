#include "C_Point.h"

CPoint::CPoint()
   : mX(0)
   , mY(0)
{}

CPoint::CPoint(float x, float y)
   : mX(x)
   , mY(y)
{}

float CPoint::getX() { return mX; }
float CPoint::getY() { return mY; }

void CPoint::setX(float x) { mX = x; }
void CPoint::setY(float y) { mY = y; }

void CPoint::moveUp(float offset) { mY += offset; }
void CPoint::moveDown(float offset) { mY -= offset; }
void CPoint::moveLeft(float offset) { mX -= offset; }
void CPoint::moveRight(float offset) { mX += offset; }

void CPoint::showCordinatesOnConsole() { cout << "x=" << mX << " y=" << mY << endl; }

CPoint::~CPoint() {};

