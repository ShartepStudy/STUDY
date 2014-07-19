#ifndef C_MY_ARRAY_H 
#define C_MY_ARRAY_H

#include <iostream>
using namespace std;

const unsigned int ALLOCATED_STEP = 10;

template<typename T>
class CMyArray
{
private:
   unsigned int mAllocatedSize;
   unsigned int mSize;
   T * mArray;
public:
   CMyArray();
   explicit CMyArray( unsigned int size );
   CMyArray( const CMyArray & obj );
   ~CMyArray();
public:
   // ��������� ���������� ���������.��� ���� ������������ �������� �� ������ ���� ���������� 
   void resize( unsigned int size );   
   // ���������� �������� � ����� ������� 
   void pushBack( T data );
   
   // �������� �������� �� ����� �������
   T popBack();             

   // ��������� �������
   void clear();       

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getIndexOf( T data ) const;

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getLastIndexOf( T data ) const;

   // ���-�� ��������� � �������
   unsigned int getSize() const;

   const T * getPTR() const;

   // ������� �������� � ������ �� ���������� �������
   void insert( unsigned int index, T data );

   // �������� �������� �� ������� �� ���������� �������
   void removeAt( unsigned int index );

   // ��������� ������� ��������� � ������� �� ���������������
   void reverse();

   // ���������� �� �����������
   void sortUp();

   // ��������� ������������� ��������� �������
   void shuffle();

public:
   CMyArray & operator=(const CMyArray & rValue);
   bool operator==( const CMyArray & rValue ) const;
   void operator()();                        // ��������� ������������� ��������� �������
   T & operator[]( unsigned int index ) const;
};

#include "MyArray.cpp"

#endif