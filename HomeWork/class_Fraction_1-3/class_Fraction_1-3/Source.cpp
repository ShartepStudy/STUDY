#include <iostream>

using namespace std;

class CFraction
{
private:
   int mCH;
   int mZN;

   int NOK( int a, int b );
   int NOD( int a, int b );
   int mod( int number );
   bool isImproper();
   void showImproper();
   void showRegular();

public:
   CFraction();
   CFraction( int ch );
   CFraction( int ch, int zn );

   void setCH( int ch );
   bool setZN( int zn );

   int getCH();
   int getZN();

   void showToConsole();
   double getFraction();
   void reducing();

   bool operator>(CFraction & obj);
   bool operator<(CFraction & obj);
   bool operator>=(CFraction & obj);
   bool operator<=(CFraction & obj);
   bool operator==(CFraction & obj);
   bool operator!=(CFraction & obj);

   CFraction operator+(CFraction & obj);
   CFraction operator-(CFraction & obj);
   CFraction operator*(CFraction & obj);
   CFraction operator/(CFraction & obj);
};






void main()
{
   CFraction A, B( 3 ), C( 7, 5 ), D( 6, 12 );
   A.showToConsole();
   B.showToConsole();
   C.showToConsole();
   D.showToConsole();
   C.reducing();
   C.showToConsole();

   A = B - C;
   A.showToConsole();


}









int CFraction::NOK( int a, int b )
{
   return mod(a * b) / NOD( a, b );
}

int CFraction::NOD( int a, int b )
{
   while (a > 0 && b > 0)

      if (a > b)
         a %= b;

      else
         b %= a;

   return a + b;
}

int CFraction::mod( int number )
{
   return number>=0 ? number : -number;
}

bool CFraction::isImproper()
{
   if (mod( mZN ) < mod( mCH )) return true;
   else return false;
}

void CFraction::showImproper()
{
   cout << mCH/mZN << '.';
   if (mCH%mZN) 
      cout << mod(mCH%mZN) << '/' << mZN << endl;
   else cout << '0' << endl;
}

void CFraction::showRegular()
{
   cout << (float) mCH/(float) mZN << endl;
}

void CFraction::reducing()
{
   int nod = NOD( mCH, mZN );
   mCH /= nod;
   mZN /= nod;
}

CFraction::CFraction()
   : mCH( 1 )
   , mZN( 1 )
{}

CFraction::CFraction( int ch )
   : mCH( ch )
   , mZN( 10 )
{}

CFraction::CFraction( int ch, int zn )
   : mCH( ch )
{
   if (zn) mZN = zn;
   else mZN = 1;
}

void CFraction::setCH( int ch )
{
   mCH = ch;
}

bool CFraction::setZN( int zn )
{
   if (zn)
   {
      mZN = zn;
      return true;
   }
   else
      return false;
}

int CFraction::getCH()
{
   return mCH;
}

int CFraction::getZN()
{
   return mZN;
}

void CFraction::showToConsole()
{
   if (isImproper()) showImproper();
   else showRegular();
}

double CFraction::getFraction()
{
   return (double) mCH/(double) mZN;
}

bool CFraction::operator>(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))>(obj.mCH*(nok/obj.mZN));
}

bool CFraction::operator<(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))<(obj.mCH*(nok/obj.mZN));
}

bool CFraction::operator>=(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))>=(obj.mCH*(nok/obj.mZN));
}

bool CFraction::operator<=(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))<=(obj.mCH*(nok/obj.mZN));
}

bool CFraction::operator==(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))==(obj.mCH*(nok/obj.mZN));
}

bool CFraction::operator!=(CFraction & obj)
{
   int nok = NOK( mZN, obj.mZN );

   return (mCH*(nok/mZN))!=(obj.mCH*(nok/obj.mZN));
}


CFraction CFraction::operator+(CFraction & obj)
{
   CFraction tmp;
   int nok = NOK( mZN, obj.mZN );
   tmp.mCH = mCH * (nok/mZN);
   tmp.mZN = nok;
   tmp.mCH += obj.mCH * (nok/obj.mZN);
   return tmp;
}

CFraction CFraction::operator-(CFraction & obj)
{
   CFraction tmp;
   int nok = NOK( mZN, obj.mZN );
   tmp.mCH = mCH * (nok/mZN);
   tmp.mZN = nok;
   tmp.mCH -= obj.mCH * (nok/obj.mZN);
   return tmp;
}

CFraction CFraction::operator*(CFraction & obj)
{
   CFraction tmp;
   tmp.mCH = mCH * obj.mCH;
   tmp.mZN = mZN * obj.mZN;
   return tmp;
}

CFraction CFraction::operator/(CFraction & obj)
{
   CFraction tmp;
   if (obj.mCH)
   {
      tmp.mCH = mCH * obj.mZN;
      tmp.mZN = mZN * obj.mCH;
   }
   return tmp;
}