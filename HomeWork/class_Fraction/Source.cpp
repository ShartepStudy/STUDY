#include "Fraction.h"
#include <iostream>
using namespace std;

//ostream& operator<<(ostream & os, const Drob & fr)
//{
//   os << fr.GetCh() << " / " << fr.GetZn() << endl;
//   return os;
//}
//
//istream& operator>>(istream & is, Drob & fr)
//{
//   cout << "Please, enter chislitel: ";
//   is >> fr.ch;
//   cout << "Please, enter znamenatel: "; 
//   is >> fr.zn;
//   return is;
//}

void main( )
{
   CFraction a, b, c, d;

   // Ввод дробей с клавиатуры
   a.input( );
   b.input( );

   // Сложение дробей
   c = a + b ;

   // Вывод суммы на экран
   c.print( );
   c.print();


}
