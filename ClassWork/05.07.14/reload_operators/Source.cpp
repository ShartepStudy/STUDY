#include <iostream>
using namespace std;

class Drob
{
   int ch;
   int zn;
public:
   // Арифметические операции
   Drob Add( Drob a );
   Drob Subtract( Drob a );
   Drob Multiply( Drob a );
   Drob Divide( Drob a );

   void Input( )
   {
      cout<<"Enter chislitel: ";
      cin>>ch;
      cout<<"Enter znamenatel: ";
      cin>>zn;
   }
   void Print( )
   {
      cout<<ch<<" / "<<zn<<"\n";
   }

   int GetCh( ) const
   {
      return ch;
   }
   int GetZn( ) const
   {
      return zn;
   }
   void Set( int ch, int zn )
   {
      this->ch = ch;
      this->zn = zn;
   }
   double GetDecimal( ) const
   {
      return (double) ch/zn;
   }

   Drob operator+(const Drob& d2)
   {
      Drob tmp;
      tmp.Set( this->GetCh( ) * d2.GetZn( ) + d2.GetCh( ) * this->GetZn( ),
               this->GetZn( ) * d2.GetZn( ) );
      return tmp;
   }

   Drob operator-()
   {
      Drob tmp;
      tmp.Set( -ch, zn );
      return tmp;
   }
   
   Drob& operator+=(const Drob& d2)
   {
      this->ch = this->ch * d2.zn + d2.ch * this->zn;
      this->zn = this->zn * d2.zn;
      return *this;
   }

   Drob& operator++()   //префиксная форма
   {
      ch += zn;
      return *this;
   }

   Drob operator++(int d)   // постфиксная форма
   {
      Drob tmp=*this;
      ch += zn;
      return tmp;
   }

   friend istream& operator>>(istream & is, Drob & fr);
};

void operator+=(Drob & d1, const Drob& d2)
{
   d1.Set(  d1.GetCh( ) * d2.GetZn( ) + d2.GetCh( ) * d1.GetZn( ),
            d1.GetZn( ) * d2.GetZn( ) );
}

//
// Арифметические операции
//

Drob Drob::Add( Drob a )
{
   Drob tmp;
   tmp.ch = ch * a.zn + a.ch * zn;
   tmp.zn = zn * a.zn;
   return tmp;
}

Drob Drob::Subtract( Drob a )
{
   Drob tmp;
   tmp.ch = ch * a.zn - a.ch * zn;
   tmp.zn = zn * a.zn;
   return tmp;
}

Drob Drob::Multiply( Drob a )
{
   Drob tmp;
   tmp.ch = ch * a.ch;
   tmp.zn = zn * a.zn;
   return tmp;
}

Drob Drob::Divide( Drob a )
{
   Drob tmp;
   tmp.ch = ch * a.zn;
   tmp.zn = zn * a.ch;
   return tmp;
}

Drob operator+(const Drob& d1, const Drob& d2)
{
   Drob tmp;
   tmp.Set( d1.GetCh( ) * d2.GetZn( ) + d2.GetCh( ) * d1.GetZn( ),
            d1.GetZn( ) * d2.GetZn( ) );
   return tmp;
}

bool operator>(const Drob& d1, const Drob& d2)
{
   return d1.GetDecimal( ) > d2.GetDecimal( );
}

Drob operator-(const Drob& d)
{
   Drob tmp;
   tmp.Set( -d.GetCh( ), d.GetZn( ) );
   return tmp;
}

ostream& operator<<(ostream & os, const Drob & fr)
{
   os << fr.GetCh() << " / " << fr.GetZn() << endl;
   return os;
}

istream& operator>>(istream & is, Drob & fr)
{
   cout << "Please, enter chislitel: ";
   is >> fr.ch;
   cout << "Please, enter znamenatel: "; 
   is >> fr.zn;
   return is;
}

void main( )
{
   Drob a, b, c, d;

   // Ввод дробей с клавиатуры
   a.Input( );
   b.Input( );

   // Сложение дробей
   c = a + b ;

   // Вывод суммы на экран
   c.Print( );
   c++;
   ++c;
   c.Print();

   cout << c;

   cin >> d;
   cout << d;
}
