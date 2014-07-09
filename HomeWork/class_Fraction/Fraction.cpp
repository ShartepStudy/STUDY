#include "Fraction.h"

CFraction::CFraction()
   : mCh(0)
   , mZn(1)
{}

CFraction::CFraction( int ch, int zn )
   : mCh( ch )
{
   if (zn) mZn = zn;
   else
   {
      cout << "ERROR!!! Divizion by ZERO!" << endl;
      exit( 0 );
   }
}

CFraction::~CFraction()
{}

void CFraction::input()
{
   cout << "Enter chislitel: ";
   cin >> mCh;
   cout << "Enter znamenatel: ";
   cin >> mZn;
}

void CFraction::print()
{
   cout << mCh << " / " << mZn << endl;
}

int CFraction::getCh() const
{
   return mCh;
}

int CFraction::getZn() const
{
   return mZn;
}

void CFraction::setCh( int ch ) 
{
   mCh = ch;
}

void CFraction::setZn( int zn )
{
   if (zn) mZn = zn;
   else
   {
      cout << "ERROR!!! Divizion by ZERO!" << endl;
      exit( 0 );
   }
}

double CFraction::getDecimal() const
{
   return (double) mCh / mZn;
}

void CFraction::reduce()
{
   int x = ( mCh < mZn ) ? mCh : mZn;
   for (int i = 2; i<=x; i++)
      if ( !(mCh%i) && !(mZn%i))
      {
         mCh /= i;
         mZn /= i;
      }
}

CFraction CFraction::operator+(const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = mCh * rValue.mZn + rValue.mCh * mZn;
   tmp.mZn = mZn * rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator+(int rValue)
{
   CFraction tmp;
   tmp.mCh = mCh + rValue * mZn;
   tmp.mZn = mZn;
   tmp.reduce();
   return tmp;
}


CFraction operator+(int lValue, const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = rValue.mCh + lValue * rValue.mZn;
   tmp.mZn = rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator-(const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = mCh * rValue.mZn - rValue.mCh * mZn;
   tmp.mZn = mZn * rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator-(int rValue)
{
   CFraction tmp;
   tmp.mCh = mCh - rValue * mZn;
   tmp.mZn = mZn;
   tmp.reduce();
   return tmp;
}


CFraction operator-(int lValue, const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = lValue * rValue.mZn - rValue.mCh;
   tmp.mZn = rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator*(const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = mCh * rValue.mCh;
   tmp.mZn = mZn * rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator*(int rValue)
{
   CFraction tmp;
   tmp.mCh = mCh * rValue;
   tmp.mZn = mZn;
   tmp.reduce();
   return tmp;
}


CFraction operator*(int lValue, const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = lValue * rValue.mCh;
   tmp.mZn = rValue.mZn;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator/(const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = mCh * rValue.mZn;
   tmp.mZn = mZn * rValue.mCh;
   tmp.reduce();
   return tmp;
}

CFraction CFraction::operator/(int rValue)
{
   CFraction tmp;
   tmp.mCh = mCh;
   tmp.mZn = mZn * rValue;
   tmp.reduce();
   return tmp;
}

CFraction operator/(int lValue, const CFraction & rValue)
{
   CFraction tmp;
   tmp.mCh = lValue * rValue.mZn;
   tmp.mZn = rValue.mCh;
   tmp.reduce();
   return tmp;
}

CFraction & CFraction::operator=(const CFraction & rValue)
{
   mCh = rValue.mCh;
   mZn = rValue.mZn;
   reduce();
   return *this;
}

CFraction & CFraction::operator=(int rValue)
{
   mCh = rValue;
   mZn = 1;
   reduce();
   return *this;
}

bool CFraction::operator==(const CFraction & rValue)
{
   return mCh*rValue.mZn == rValue.mCh*mZn;
}

bool CFraction::operator!=(const CFraction & rValue)
{
   return mCh*rValue.mZn != rValue.mCh*mZn;
}

bool CFraction::operator<(const CFraction & rValue)
{
   return mCh*rValue.mZn < rValue.mCh*mZn;
}

bool CFraction::operator>(const CFraction & rValue)
{
   return mCh*rValue.mZn > rValue.mCh*mZn;
}

bool CFraction::operator<=(const CFraction & rValue)
{
   return mCh*rValue.mZn <= rValue.mCh*mZn;
}

bool CFraction::operator>=(const CFraction & rValue)
{
   return mCh*rValue.mZn >= rValue.mCh*mZn;
}







