#include <list>
#include <iterator>
#include <iostream>

using namespace std;
int main()
{
	list<int> b;
	list<int> b1;
	list<int>::iterator pb;
	
	//создание итератора вставки в начало контейнера
	//в конструктор передаетс€ контейнер
	front_insert_iterator<list<int> > bi(b);
	front_insert_iterator<list<int> > bi1(b1);

	//вставка элементов в начало контейнера
	for(int i = 0; i < 10; i++, bi++) *bi = i;
	
	cout << "Initial list: " << endl;
	for(pb = b.begin(); pb != b.end(); pb++) cout << *pb << " ";
	cout << endl;

	//копирование данных с помощью итератора вставки:
	copy(b.begin(),b.end(),bi1);

      cout << "Copy of list: " << endl;
	for(pb = b1.begin(); pb != b1.end(); pb++) cout << *pb << " ";
	cout << endl;
	
	//добавление 2 элементов с использованием функции front_inserter
	front_inserter(b1) = 11;
	front_inserter(b1) = 12;
	cout << "Add some new data: " << endl;
	for(pb = b1.begin(); pb != b1.end(); pb++) cout << *pb << " ";

	return 0;
}
