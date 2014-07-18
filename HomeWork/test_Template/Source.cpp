#include<iostream>
using namespace std;

#include "TestTemplate.h"



void main()
{
   CTestTemplate<char> str( "Hello Word" );

   cout << str.getData() << endl;
}