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
   // изменение количества элементов.при этом существующие элементы не должны быть уничтожены 
   void resize( unsigned int size );   
   // добавление элемента в конец массива 
   void pushBack( T data );
   
   // удаление элемента из конца массива
   T popBack();             

   // обнуление массива
   void clear();       

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getIndexOf( T data ) const;

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getLastIndexOf( T data ) const;

   // кол-во элементов в массиве
   unsigned int getSize() const;

   const T * getPTR() const;

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
   CMyArray & operator=(const CMyArray & rValue);
   bool operator==( const CMyArray & rValue ) const;
   void operator()();                        // повторная инициализация элементов массива
   T & operator[]( unsigned int index ) const;
};

#include "MyArray.cpp"

#endif