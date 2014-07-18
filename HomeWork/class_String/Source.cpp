#include "MyString.h"

void main()
{
   CMyString A("Hello Word!!!");
   CMyString B( A );
   CMyString C;


   cout << A << endl;
   cout << B << endl;
   C = "PTN PTX!!!";
   if (A==B) 
      cout << C << endl;
   if (A=="Hello Word!!!") 
      cout << C << endl;
}