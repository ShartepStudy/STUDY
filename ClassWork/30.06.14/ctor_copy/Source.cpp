#include <iostream>
using namespace std;

class A 
{
	int age;
	char * name;
public:
	A(){};
	A(int a, char * n)
	{
		age=a;
		name = new char(strlen(n)+1);
		strcpy(name, n);
	}
	void setAge(int a) {age = a;}
	void setName(char * n)
	{
		name = new char(strlen(n)+1);
		strcpy(name, n);
	}
	int getAge() { return age; }
	const char * getName() { return name; }
};

void main()
{
	A a;
	a.setAge(25);
	a.setName("VASYA");

	A b=a;
	A c(5, "Kolya");

	cout << b.getAge() << endl;
	cout << b.getName() << endl;

	cout << c.getAge() << endl;
	cout << c.getName() << endl;
	
}