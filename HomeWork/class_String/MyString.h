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
   explicit CMyString( const char * str );
   CMyString( const CMyString & obj );

   CMyString( const char * str, unsigned int capacity );
   CMyString( const CMyString & obj, unsigned int capacity );

   ~CMyString();
public:
   const char * c_str() const;
public:
   CMyString & operator=(const CMyString & rValue);
   CMyString & operator=(const char * str);

   bool operator==(const CMyString & rValue) const;
   bool operator==(const char * str) const;
   friend bool operator==(const char * str, const CMyString & rValue);

   bool operator!=(const CMyString & rValue) const;
   bool operator!=(const char * str) const;
   friend bool operator!=(const char * str, const CMyString & rValue);

   bool operator>(const CMyString & rValue) const;
   bool operator>(const char * str) const;
   friend bool operator>(const char * str, const CMyString & rValue);

   bool operator<(const CMyString & rValue) const;
   bool operator<(const char * str) const;
   friend bool operator<(const char * str, const CMyString & rValue);

   bool operator>=(const CMyString & rValue) const;
   bool operator>=(const char * str) const;
   friend bool operator>=(const char * str, const CMyString & rValue);

   bool operator<=(const CMyString & rValue) const;
   bool operator<=(const char * str) const;
   friend bool operator<=(const char * str, const CMyString & rValue);

   CMyString & operator()( const CMyString & rValue );
   CMyString & operator()( const char * str );

   char & operator[]( unsigned int index );

   friend ostream & operator<<(ostream & os, CMyString & obj);
};



#endif
