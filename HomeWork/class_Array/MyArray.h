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
   // изменение количества элементов.при этом существующие элементы не должны быть уничтожены 
   void resize( unsigned int size );   
   // добавление элемента в конец массива 
   void pushBack( T data );
   //{
   //   if (mSize >= mAllocatedSize)
   //      resize( mAllocatedSize + ALLOCATED_STEP );

   //   mArray[mSize++] = data;
   //}
   
   // удаление элемента из конца массива
   int popBack();             

   // обнуление массива
   void clear();       

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getIndexOf( T data );

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getLastIndexOf( T data );

   // вставка элемента в массив по указанному индексу
   void insert( unsigned int index, T data );

   // удаление элемента из массива по указанному индексу
   void removeAt( unsigned int index );

   // изменение порядка элементов в массиве на противоположный
   void reverse();

   // сортировка по возрастанию
   void sortUp();

   // случайное перемешивание элементов массива
   void shuffle();

public:
   bool operator==( const CMyArray & rValue );
   void operator()();                        // повторная инициализация элементов массива
   int & operator[]( unsigned int index );
};

#endif