#include "MyString.h"


CMyString::CMyString()
   : mArray(80)
{
   mArray.pushBack( '\0' );
}

CMyString::CMyString( unsigned int capacity )
   : mArray( capacity > 10 ? capacity : 10 )
{
   mArray.pushBack( '\0' );
}

CMyString::CMyString( const char * str )
{
   while (*str)
      mArray.pushBack( *(str++) );
   
   mArray.pushBack( '\0' );
}

CMyString::CMyString( const CMyString & obj )
   : mArray(obj.mArray)
{}

CMyString::CMyString( const char * str, unsigned int capacity )
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
const char * CMyString::c_str() const
{
   return mArray.getPTR();
}




//---------------------------------------------------------------------------------------

CMyString & CMyString::operator=(const char * str)
{
   mArray.clear();
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

bool CMyString::operator==(const char * str) const
{
   return !strcmp( c_str(), str );
}

bool CMyString::operator==(const CMyString & rValue) const
{
   return mArray == rValue.mArray;
}

bool operator==(const char * str, const CMyString & rValue)
{
   return rValue==str;
}

bool CMyString::operator!=(const char * str) const
{
   return !(*this==str);
}

bool CMyString::operator!=(const CMyString & rValue) const
{
   return !(*this==rValue);
}

bool operator!=(const char * str, const CMyString & rValue)
{
   return !(rValue==str);
}

bool CMyString::operator>(const CMyString & rValue) const 
{
   return strcmp( c_str(), rValue.c_str() )>0 ? true : false ; 
}

bool CMyString::operator>(const char * str) const
{
   return strcmp( c_str(), str )>0 ? true : false;
}

bool operator>(const char * str, const CMyString & rValue)
{
   return strcmp( str, rValue.c_str() )>0 ? true : false;
}

bool CMyString::operator<(const CMyString & rValue) const
{
   return strcmp( c_str(), rValue.c_str() )<0 ? true : false;
}

bool CMyString::operator<(const char * str) const
{
   return strcmp( c_str(), str )<0 ? true : false;
}

bool operator<(const char * str, const CMyString & rValue)
{
   return strcmp( str, rValue.c_str() )<0 ? true : false;
}

bool CMyString::operator>=(const CMyString & rValue) const
{
   return strcmp( c_str(), rValue.c_str() )>=0 ? true : false;
}

bool CMyString::operator>=(const char * str) const
{
   return strcmp( c_str(), str )>=0 ? true : false;
}

bool operator>=(const char * str, const CMyString & rValue)
{
   return strcmp( str, rValue.c_str() )>=0 ? true : false;
}

bool CMyString::operator<=(const CMyString & rValue) const
{
   return strcmp( c_str(), rValue.c_str() )<=0 ? true : false;
}

bool CMyString::operator<=(const char * str) const
{
   return strcmp( c_str(), str )<=0 ? true : false;
}

bool operator<=(const char * str, const CMyString & rValue)
{
   return strcmp( str, rValue.c_str() )<=0 ? true : false;
}

CMyString & CMyString::operator()( const CMyString & rValue )
{
   *this = rValue;
   return *this;
}

CMyString & CMyString::operator()( const char * str )
{
   *this = str;
   return *this;
}

char & CMyString::operator[]( unsigned int index )
{
   return mArray[index];
}


ostream & operator<<(ostream & os, CMyString & obj)
{
   os << obj.c_str();
   return os;
}

