#include <list>
#include <iterator>
#include <iostream>

using namespace std;
int main()
{
	list<int> b;
	list<int> b1;
	list<int>::iterator pb;
	
	//создание итератора вставки в конец контейнера
	//в конструктор передается контейнер
	back_insert_iterator<list<int> > bi(b);
	back_insert_iterator<list<int> > bi1(b1);

	//вставка элементов в конец контейнера
	for(int i = 0; i < 10; i++, bi++) *bi = i;
	
	cout << "Initial list: " << endl;
	for(pb = b.begin(); pb != b.end(); pb++) cout << *pb << " ";
	cout << endl;

	//copy(b.begin(),b.end(),b1.end());
	//Этот вызов приведет к ошибке времени выполнения, т.к. обычный итератор 
      //не позволяет расширить контейнер
	//это можно сделать с помощью итератора вставки:
	copy(b.begin(),b.end(),bi1);

      cout << "Copy of list: " << endl;
	for(pb = b1.begin(); pb != b1.end(); pb++) cout << *pb << " ";
	cout << endl;
	
	//добавление 2 элементов с использованием функции back_inserter
	back_inserter(b1) = 11;
	back_inserter(b1) = 12;
	cout << "Add some new data: " << endl;
	for(pb = b1.begin(); pb != b1.end(); pb++) cout << *pb << " ";

	return 0;
}
