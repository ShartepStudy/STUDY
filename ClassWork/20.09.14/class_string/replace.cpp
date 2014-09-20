#include <iostream>
#include <string>

void main() {
  std::string s("V sybboty Alex hodit na paru, a potom Alex hodit v kino, zatem Alex spit, potom Alex zavtrakaet!!!");
  std::cout << s << std::endl;

  size_t poss = 0;
  while (std::string::npos != (poss = s.find("Alex"))) {
    s.replace(poss, 4, "Vasya");
  }

  std::cout << s << std::endl;
}