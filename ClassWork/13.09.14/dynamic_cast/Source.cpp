#include <iostream>
using namespace std;

class B {
public:
  virtual void Test() {
    cout << "Test B\n\n";
  }
};

class D : public B {
public:
  void Test() {
    cout << "Test D\n\n";
  }
};

void main() {

  B b;
  D d;

  B *pb;
  D *pd;

  pd = dynamic_cast<D*> (&d);
  if (pd) {
    cout << "1 OK!\n";
    pd->Test();
  } else cout << "Error 1\n";

  ////////////////////////////////////////

  pb = dynamic_cast<B*> (&d);
  if (pb) {
    cout << "2 OK!\n";
    pb->Test();
  } else cout << "Error 2\n";

  ////////////////////////////////////////

  pb = dynamic_cast<B*> (&b);
  if (pb) {
    cout << "3 OK!\n";
    pb->Test();
  } else cout << "Error 3\n";

  ////////////////////////////////////////

  pd = dynamic_cast<D*> (&b);
  if (pd) {
    cout << "4 OK!\n";
    pd->Test();
  } else cout << "Error 4\n";
}