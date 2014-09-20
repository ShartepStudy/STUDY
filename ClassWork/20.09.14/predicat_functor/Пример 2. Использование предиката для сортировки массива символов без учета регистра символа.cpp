#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

//перевод символа в верхний регистр
bool cmp(char a, char b)
{
	if ((a >= 'a') && (a <= 'z')) a = a - 'a' + 'A';
	if ((b >= 'a') && (b <= 'z')) b = b - 'a' + 'A';
	return a < b;
}

int main()
{
	char ar[] = {'a','h','A','K','b','z','X','I'};
	vector<char> a(ar,ar+8);
	ostream_iterator<char> out(cout," ");

	cout << "Initial state: " << endl;
	copy(a.begin(),a.end(),out); 
	cout << endl;

	sort(a.begin(),a.end(),cmp);

	cout << "After sort: " << endl;
	copy(a.begin(),a.end(),out); 
	cout << endl;

	return 0;
}
