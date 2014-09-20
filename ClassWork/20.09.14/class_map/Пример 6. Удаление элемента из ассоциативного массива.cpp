#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	map <string, string> m;
	// Заполнение карты названиями городов и достопримечательностями
	m.insert(make_pair("Leningrad","Winter Palace"));
	m.insert(make_pair("London","Big Ben"));
	m.insert(make_pair("Parice","Louvre"));

	map <string, string>::iterator it;
	cout << "Initial State: " << endl;
	for(it = m.begin(); it != m.end(); it++)
  	 cout << it->first << " " << it->second << endl;

	// Ленинград переименовали
    // непосредсвенно ключ заменить нельзя:
	// m.begin()->first = "Peregburg"; // ошибка присвоения значения операнду типа const string
	// Для изменения надо удалить, а потом добавить: 
	m.erase("Leningrad");
	m.insert(make_pair("Peregburg","Winter Palace"));
	cout << endl << "After change key: " << endl;
	for(it = m.begin(); it != m.end(); it++)
  	 cout << it->first << " " << it->second << endl;
}
