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
   //   : mAllocatedSize( ALLOCATED_STEP )
   //   , mSize( 0 )
   //   , mArray( new T[mAllocatedSize] )
   //{
   //   for (size_t i = 0; i < mAllocatedSize; i++)
   //      mArray[i] = 0;
   //}
   CMyArray( unsigned int size );
   //   : mAllocatedSize( size )
   //   , mSize( 0 )
   //   , mArray( new T[mAllocatedSize] )
   //{
   //   for (size_t i = 0; i < mAllocatedSize; i++)
   //      mArray[i] = 0;
   //}
//   CMyArray( const CMyArray & obj );
   ~CMyArray();
   //{
   //   delete[] mArray;
   //}
public:
   // ��������� ���������� ���������.��� ���� ������������ �������� �� ������ ���� ���������� 
   void resize( unsigned int size );   
   // ���������� �������� � ����� ������� 
   void pushBack( T data );
   //{
   //   if (mSize >= mAllocatedSize)
   //      resize( mAllocatedSize + ALLOCATED_STEP );

   //   mArray[mSize++] = data;
   //}
   
   // �������� �������� �� ����� �������
   int popBack();             

   // ��������� �������
   void clear();       

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getIndexOf( T data );

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getLastIndexOf( T data );

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
   bool operator==( const CMyArray & rValue );
   void operator()();                        // ��������� ������������� ��������� �������
   int & operator[]( unsigned int index );
};

#endif

#include "MyArray.cpp"
