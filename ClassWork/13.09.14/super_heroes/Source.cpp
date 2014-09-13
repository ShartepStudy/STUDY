#include <iostream>
#include <typeinfo>
#include <ctime>
using namespace std;

class SuperHero {
public:
  char name[20];
public:
  virtual void ShowName() {
    cout << name;
  }
  virtual ~SuperHero() = 0;
};

/////////////////////////////////////////////////////////////////

class Ability abstract {

};

class Flight : public Ability {
public:
  virtual void Fly() = 0;
};

class SuperStrength : public Ability {

};

class SuperSpeed : public Ability {
public:
  virtual void Run() = 0;
};

class XRayVision : public Ability {
public:
  virtual void AirportSecurityGuard() = 0;
};

/////////////////////////////////////////////////////////////////

class Batman : public SuperHero, public Flight, public SuperStrength {
public:
  Batman() {
    strcpy(name, "Batman");
  }
  void Fly() {
    cout << "Batman Fly!\n";
  }
};

class SuperMan : public SuperHero, public Flight, public SuperStrength, public SuperSpeed, public XRayVision {
public:
  SuperMan() {
    strcpy(name, "SuperMan");
  }
  void Fly() {
    cout << "SuperMan Fly!\n";
  }
  void Run() {
    cout << "SuperMan Run!\n";
  }
  void AirportSecurityGuard() {
    cout << "SuperMan AirportSecurityGuard!\n";
  }
};

class CatWoman : public SuperHero {
public:
  CatWoman() {
    strcpy(name, "CatWoman");
  }
};

class SpiderMan : public SuperHero {
public:
  SpiderMan() {
    strcpy(name, "SpiderMan");
  }
};

int main() {
  srand(time(0));

  int count_of_superheroes = 15;
  SuperHero **heroes = new SuperHero*[count_of_superheroes];

  for (int i = 0; i < count_of_superheroes; i++) {
    int r = rand() % 4;

    if (r == 0) heroes[i] = new Batman();
    else if (r == 1) heroes[i] = new SuperMan();
    else if (r == 2) heroes[i] = new CatWoman();
    else if (r == 3) heroes[i] = new SpiderMan();

    cout << i + 1 << ". ";
    heroes[i]->ShowName();

    cout << typeid(*heroes[i]).name() << "\n";

    if (dynamic_cast<Flight*> (heroes[i]))
      cout << " - Can Fly!";

    cout << "\n";
  }
}
