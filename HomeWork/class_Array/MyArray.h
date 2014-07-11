#pragma once

#include <iostream>
using namespace std;

const unsigned int ALLOCATED_STEP = 10;

class CMyArray
{
private:
   unsigned int mAllocatedSize;
   unsigned int mSize;
   int * mArray;
public:
   CMyArray();
   CMyArray(int size);
   CMyArray(const CMyArray & obj);
   ~CMyArray();
public:
   // ��������� ���������� ���������.��� ���� ������������ �������� �� ������ ���� ���������� 
   void resize( unsigned int size );   
   
   // ���������� �������� � ����� ������� 
   void pushBack( int data ); 
   
   // �������� �������� �� ����� �������
   int popBack();             

   // ��������� �������
   void clear();       

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getIndexOf( int data );

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getLastIndexOf( int data );

   // ������� �������� � ������ �� ���������� �������
   void insert( unsigned int index, int data );

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

