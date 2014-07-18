#include "MyString.h"


CMyString::CMyString()
   : mArray(80)
{}

CMyString::CMyString( unsigned int capacity )
   : mArray( capacity > 10 ? capacity : 10 )
{}

CMyString::CMyString( char * str )
{
   while (*str)
      mArray.pushBack( *(str++) );
   
   mArray.pushBack( '\0' );
}

CMyString::CMyString( const CMyString & obj )
   : mArray(obj.mArray)
{}

CMyString::CMyString( char * str, unsigned int capacity )
   : mArray( capacity )
{
   while (str)
      mArray.pushBack( *(str++) );

   mArray.pushBack( '\0' );
}

CMyString::CMyString( const CMyString & obj, unsigned int capacity )
   : mArray( obj.mArray )
{
   if ( mArray.getSize()<capacity )
      mArray.resize( capacity );
}

CMyString::~CMyString()
{}

//---------------------------------------------------------------------------------------
const char * CMyString::c_str()
{
   return mArray.getPTR();
}




//---------------------------------------------------------------------------------------

CMyString & CMyString::operator=(char * str)
{
   while (*str)
      mArray.pushBack( *(str++) );

   mArray.pushBack( '\0' );
   return *this;
}

CMyString & CMyString::operator=(const CMyString & rValue)
{
   mArray = rValue.mArray;
   return *this;
}

bool CMyString::operator==(char * str)
{
   return !strcmp( c_str(), str );
}

bool CMyString::operator==(const CMyString & rValue)
{
   return mArray == rValue.mArray;
}

ostream & operator<<(ostream & os, CMyString & obj)
{
   os << obj.c_str();
   return os;
}

