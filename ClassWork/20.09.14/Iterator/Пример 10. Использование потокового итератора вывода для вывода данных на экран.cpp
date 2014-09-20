#include <iterator>
#include <iostream>

using namespace std;
int main()
{
	char a[] = {'a','b','c'};
	//вывод данных на экран с использованием итератора вывода
    //в конструктор передается поток, в который надо
	//осуществлять вывод и разделитель 

	//без разделителя
	ostream_iterator<char> out(cout);
	cout << "Without delimeter: " << endl;
	copy(a,a+3,out);
	cout << endl;

	//в качестве разделителя используется табуляция
    ostream_iterator<char> out1(cout,"\t");
	cout << "Without tab delimeter: " << endl;
    copy(a,a+3,out1);
	return 0;
}
