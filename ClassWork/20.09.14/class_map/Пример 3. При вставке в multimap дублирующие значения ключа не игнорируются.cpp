#include <iostream>
#include <string>
#include <map>
using namespace std;

//для сокращения записи вводим обозначение:
typedef multimap<int,string> MyMap;
typedef MyMap::iterator Iter;
int main()
{
	//начальная инициализация map
	MyMap m;
	//использование value_type для формирование пары "ключ - значение"
	m.insert(MyMap::value_type(3,"Ivanov"));
	//можно непосредственно использовать тип pair
	m.insert(pair<int,string>(2,"Petrov"));
	//использование функции make_pair
	// при вставке в multimap дублирующие значения ключа не игнорируются 
	m.insert(make_pair(3,"Sidorov"));

	for(Iter it = m.begin(); it != m.end(); it++)
	{
		//использование свойств итератора:
		//first для обращения к ключу,
		//second для обращение к значению
		cout << it->first << " " << it->second << endl;
	}
	
	return 0;
}
