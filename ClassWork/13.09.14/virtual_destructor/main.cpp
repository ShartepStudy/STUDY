#include <iostream>
#include <conio.h>
using namespace std;

class Transport {
protected:
  double skorost;
public:
  Transport() {
    cout << "Default c-tor base class!\n";
  }
  virtual ~Transport(){
  cout<<"Destructor of base class!\n";
  }

};

class Gruzovik : public Transport {
  char*gruz;
public:
  Gruzovik() {
    cout << "Default c-tor Gruzovik!\n";
    gruz = new char[100000];
  }
  ~Gruzovik() {
    cout << "Gruzovik Destructor\n";
    delete[]gruz;
  }
};

class Marshrutka : public Transport {
  int*passazhirs;
public:
  Marshrutka() {
    cout << "Default c-tor Marshrutka!\n";
    passazhirs = new int[rand() % 40];
  }
  ~Marshrutka() {
    cout << "Marshrutka Destructor\n";
    delete[]passazhirs;
  }
};

void main() {
  Transport* t[2];
  t[0] = new Gruzovik;
  getch();
  cout << "\n";

  t[1] = new Marshrutka;
  getch();
  cout << "\n";

  for (int i = 0; i<2; i++)
    delete t[i];

  cout << "\n";
}