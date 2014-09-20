#include <string>
#include <iostream>
using namespace std;
int main()
{
	string s("How long this string?");
	cout << "s.length() = " << s.length() << endl;
	cout << "s.size() = " << s.size() << endl;
	cout << "s.max_size() = " << hex << s.max_size() << endl;
	cout << "s.capacity() = " << dec <<s.capacity() << endl;
	s.reserve(120);
	cout << "After reservation" << endl;
	cout << "s.capacity() = " << s.capacity() << endl;
	return 0;
}
