#ifndef C_MY_STRING_H
#define C_MY_STRING_H

#include "MyArray.h"

class CMyString
{
private:
   CMyArray<char> mArray;
public:
   CMyString();

   explicit CMyString( unsigned int capacity );
   explicit CMyString( char * str );
   CMyString( const CMyString & obj );

   CMyString( char * str, unsigned int capacity );
   CMyString( const CMyString & obj, unsigned int capacity );

   ~CMyString();
public:
   const char * c_str();
public:
   CMyString & operator=(char * str);
   CMyString & operator=(const CMyString & rValue);

   bool operator==(char * str);
   bool operator==(const CMyString & rValue);
   
   friend ostream & operator<<(ostream & os, CMyString & obj);
};


#endif
