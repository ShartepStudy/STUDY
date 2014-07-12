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
   // изменение количества элементов.при этом существующие элементы не должны быть уничтожены 
   void resize( unsigned int size );   
   
   // добавление элемента в конец массива 
   void pushBack( int data ); 
   
   // удаление элемента из конца массива
   int popBack();             

   // обнуление массива
   void clear();       

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getIndexOf( int data );

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getLastIndexOf( int data );

   // вставка элемента в массив по указанному индексу
   void insert( unsigned int index, int data );

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

