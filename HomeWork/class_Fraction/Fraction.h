#ifndef C_FRACTION_H
#define C_FRACTION_H

#include <iostream>
using namespace std;

class CFraction
{
   int mCh;
   int mZn;
public:
   CFraction();
   CFraction( int ch, int zn );
   ~CFraction();

public:
   void input();
   void print();
   int getCh() const;
   int getZn() const;
   void setCh( int ch );
   void setZn( int zn );
   double getDecimal() const;
   void reduce();

public:
   CFraction operator+(const CFraction & rValue);
   CFraction operator+(int rValue);
   friend CFraction operator+(int lValue, const CFraction & rValue);

   CFraction operator-(const CFraction & rValue);
   CFraction operator-(int rValue);
   friend CFraction operator-(int lValue, const CFraction & rValue);

   CFraction operator*(const CFraction & rValue);
   CFraction operator*(int rValue);
   friend CFraction operator*(int lValue, const CFraction & rValue);

   CFraction operator/(const CFraction & rValue);
   CFraction operator/(int rValue);
   friend CFraction operator/(int lValue, const CFraction & rValue);

   CFraction & operator=(const CFraction & rValue);
   CFraction & operator=(int rValue);

   bool operator==(const CFraction & rValue);
   bool operator!=(const CFraction & rValue);
   bool operator<(const CFraction & rValue);
   bool operator>(const CFraction & rValue);
   bool operator<=(const CFraction & rValue);
   bool operator>=(const CFraction & rValue);
};




#endif