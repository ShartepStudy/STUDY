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
   // изменение количества элементов.при этом существующие элементы не должны быть уничтожены 
   bool resize( int size );   
   
   // добавление элемента в конец массива 
   bool pushBack( int data ); 
   
   // удаление элемента из конца массива
   int popBack();             

   // обнуление массива
   void clear();       

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getIndexOf( int data ); 

   // проверка на вхождение элемента в массив. в результате работы возвращает индекс первого найденного элемента. eсли ничего не найдено, возвращает -1.
   int getLastIndexOf( int data );

   // вставка элемента в массив по указанному индексу
   void insert( int index, int data );

   // удаление элемента из массива по указанному индексу
   void removeAt( int index );

   // изменение порядка элементов в массиве на противоположный
   void reverse();

   // сортировка по возрастанию
   void sortUp();

   // случайное перемешивание элементов массива
   void shuffle();

public:
   bool operator==(const CMyArray & rValue);
   void operator()();                        // повторная инициализация элементов массива
   void operator[]( int index );
};

