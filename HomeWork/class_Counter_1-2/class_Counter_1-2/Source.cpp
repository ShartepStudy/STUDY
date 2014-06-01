#include <iostream>
using namespace std;

class CCounter
{
private:
   int mMax;
   int mMin;
   int mStep;
   int mCurrent;
public:
   CCounter();
   CCounter( int min, int max );
   CCounter( int min, int max, int step, int current );

   void add();
   void addStep();
   void reset();

   int getCurrent();
   int getMax();
   int getMin();
   int getStep();

   void setCurrent( int current );
   void setMax( int max );
   void setMin( int min );
   void setStep( int step );
};

CCounter::CCounter()
   : mMax( 99999 )
   , mMin( 0 )
   , mStep( 1 )
   , mCurrent( 0 )
{}

CCounter::CCounter( int min, int max )
   : mMax( max )
   , mMin( min )
   , mStep( 1 )
   , mCurrent( min )
{}

CCounter::CCounter( int min, int max, int step, int current )
   : mMax( max )
   , mMin( min )
   , mStep( step )
   , mCurrent( current )
{}

void CCounter::add()
{
   mCurrent++;
   if( mCurrent>mMax ) reset();
}

void CCounter::addStep()
{
   mCurrent += mStep;
   if( mCurrent>mMax ) reset();
}

void CCounter::reset()
{
   mCurrent = mMin;
}

int CCounter::getCurrent()
{
   return mCurrent;
}

int CCounter::getMax()
{
   return mMax;
}

int CCounter::getMin()
{
   return mMin;
}
int CCounter::getStep()
{
   return mMax;
}

void CCounter::setCurrent( int current )
{
   mCurrent = current;
}

void CCounter::setMax( int max )
{
   mMax = max;
}

void CCounter::setMin( int min )
{
   mMin = min;
}

void CCounter::setStep( int step )
{
   mStep = step;
}

void main()
{
   CCounter A, B( -5, 589 ), C( -10, 9999, 2, 5 );

   cout << A.getCurrent() << "\t" << B.getCurrent() << "\t" << C.getCurrent() << endl;

   A.add();
   B.addStep();
   C.reset();

   cout << A.getCurrent() << "\t" << B.getCurrent() << "\t" << C.getCurrent() << endl;

}