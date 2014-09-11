#include <iostream>
using namespace std;

class A
{
public:
   A() { cout << "Class A constructor!\n"; }
   ~A() { cout << "Class A destructor!\n"; }
   void f() { cout << "A::f" << "\n"; }
};

class B : public A
{
public:
   B() { cout << "Class B constructor!\n"; }
   ~B() { cout << "Class B destructor!\n"; }
   void f(int g) { cout << "B::f " << g << "\n";  }
};

class C : public B
{
public:
   C() { cout << "Class C constructor!\n"; }
   ~C() { cout << "Class C destructor!\n"; }
};

void main()
{
   A a;
   _sleep(2000);
   B b;
   _sleep(2000);
   C c;
   _sleep(2000);
   cout << "\n\n";

   b.f();
   b.f(5);
}
