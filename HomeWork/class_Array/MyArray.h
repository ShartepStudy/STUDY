#pragma once
class CMyArray
{
private:
   int * mArray;
   unsigned int mSize;
public:
   CMyArray();
   CMyArray(int size);
   CMyArray(const CMyArray & obj);
   ~CMyArray();
public:
   // ��������� ���������� ���������.��� ���� ������������ �������� �� ������ ���� ���������� 
   bool resize( int size );   
   
   // ���������� �������� � ����� ������� 
   bool pushBack( int data ); 
   
   // �������� �������� �� ����� �������
   int popBack();             

   // ��������� �������
   void clear();       

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getIndexOf( int data ); 

   // �������� �� ��������� �������� � ������. � ���������� ������ ���������� ������ ������� ���������� ��������. e��� ������ �� �������, ���������� -1.
   int getLastIndexOf( int data );

   // ������� �������� � ������ �� ���������� �������
   void insert( int index, int data );

   // �������� �������� �� ������� �� ���������� �������
   void removeAt( int index );

   // ��������� ������� ��������� � ������� �� ���������������
   void reverse();

   // ���������� �� �����������
   void sortUp();

   // ��������� ������������� ��������� �������
   void shuffle();

public:
   bool operator==(const CMyArray & rValue);
   void operator()();                        // ��������� ������������� ��������� �������
   void operator[]( int index );
};

