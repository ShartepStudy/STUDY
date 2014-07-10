#include "MyArray.h"

CMyArray::CMyArray()
{}

CMyArray::CMyArray( int size );

CMyArray::CMyArray( const CMyArray & obj );

CMyArray::~CMyArray()
{}

bool CMyArray::resize( int size );

bool CMyArray::pushBack( int data );

int CMyArray::popBack();

void CMyArray::clear();

int CMyArray::getIndexOf( int data );

int CMyArray::getLastIndexOf( int data );

void CMyArray::insert( int index, int data );

void CMyArray::removeAt( int index );

void CMyArray::reverse();

   // сортировка по возрастанию
   void sortUp();

   // случайное перемешивание элементов массива
   void shuffle();

public:
   bool operator==(const CMyArray & rValue);
   void operator()();                        // повторная инициализация элементов массива
   void operator[]( int index );