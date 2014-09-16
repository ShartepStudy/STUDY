#include <iostream>
using namespace std;

void main() {

  const int r = 10;

  //int& s = r; // нельзя вот так просто взять и создать ссылку на константу
  int& s = const_cast <int&> (r); // снимаем конст на секундочку
  //int& s = const_cast <int> (r); // конст каст применяется только при работе с указателями или ссылками

  s++; // было 10, стало 11

  cout << const_cast <int&> (r) << "\n";

  const_cast <int&> (r)++; // было 11, стало 12
  //const_cast <double&> (r)++; // так нельзя, можно снять конст, но нельзя поменять тип
  //r++; // так тоже сделать нельзя

  cout << s << "\n"; // 12
  cout << r << "\n"; // 10


}