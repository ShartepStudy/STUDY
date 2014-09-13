#include <iostream>
using namespace std;

void main() {

  int x = 5;

  int* mass = new int[10];

  x = reinterpret_cast <int> (mass);
  //x = mass; // так нельзя

  cout << mass << "\n";

  cout << x << "\n";
  //cout<< (int) mass <<"\n"; // 

  char*** mass2 = new char**[10];
  x = reinterpret_cast <int> (mass2);

  char y = 'A';
  //x = reinterpret_cast <int> (y);
}