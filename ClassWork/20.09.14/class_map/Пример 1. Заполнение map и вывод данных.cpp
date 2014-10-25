#include <iostream>
#include <string>
#include <map>
using namespace std;

//для сокращения записи вводим обозначение:
typedef map<int,string> MyMap;
typedef MyMap::iterator Iter;
int main()
{
	//начальная инициализация map
	MyMap m;
	//использование value_type для формирование пары "ключ - значение"
	m.insert(MyMap::value_type(1,"Ivanov"));
	//можно непосредственно использовать тип pair
	m.insert(pair<int,string>(2,"Petrov"));
	//использование функции make_pair
	m.insert(make_pair(3,"Sidorov"));


	for(auto x: m)
	{
		//использование свойств итератора:
		//first для обращения к ключу,
		//second для обращение к значению
		cout << x.first << " " << x.second << endl;
	}
	
	return 0;
}
