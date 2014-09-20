#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class cmp
{
 int Val;
 public:
	 cmp(int iVal) : Val(iVal) {}
	 //оператор () используется для сравнения элементов
       //контейнера со значением, сохраненным в классе
	bool operator() (int a) {return a < Val;}
};

int main()
{
	//объявление и заполнение списка
	int ar[] = {1,3,2,5,8,6,7,9,4,0};
	list<int> a = list<int>(ar, ar+10);
	ostream_iterator<int> out(cout, " ");
	//вывод начального состояни списка
	cout << "Initial state: " << endl;
	copy(a.begin(), a.end(), out); 
	cout << endl;

	//удаление элементов со значением < 3 с использованием функтора
	a.remove_if(cmp(3));
    cout << endl << "After remove less then 3: " << endl;
    copy(a.begin(), a.end(), out); 
	cout << endl;

	//удаление элементов со значением < 6 с использованием функтора
	a.remove_if(cmp(6));
	cout << endl << "After remove less then 6: " << endl;
    copy(a.begin(), a.end(), out); 
	cout << endl;
	
	return 0;
}