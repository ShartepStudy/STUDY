#include <iostream>
using namespace std;

class A {
public:
	A() {
		f2();
	}

	void f1() {
		cout << "A::f1()\n";
	}

	void f2() {
		cout << "A::f2()\n";
	}
};

class B : public A {
public:
	void f2() {
		cout ;
	}
};

void main() {
	B b;
	b.f2();
	b.f1();
}