#include <list>
#include <iostream>

using namespace std;
int main()
{
	list<int> b;

	for(int i = 0; i < 3; i++) b.push_back(i);
	
	list<int>::iterator pb;

	//итератор поддерживает сравнение != и оператор ++
	for(pb = b.begin(); pb != b.end(); pb++) 
		cout << *pb << " ";
	cout << endl;

	return 0;
}
