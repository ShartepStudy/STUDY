#include <iostream>
using namespace std;

void main() {

  const int r = 10;

  //int& s = r; // ������ ��� ��� ������ ����� � ������� ������ �� ���������
  int& s = const_cast <int&> (r); // ������� ����� �� ����������
  //int& s = const_cast <int> (r); // ����� ���� ����������� ������ ��� ������ � ����������� ��� ��������

  s++; // ���� 10, ����� 11

  cout << const_cast <int&> (r) << "\n";

  const_cast <int&> (r)++; // ���� 11, ����� 12
  //const_cast <double&> (r)++; // ��� ������, ����� ����� �����, �� ������ �������� ���
  //r++; // ��� ���� ������� ������

  cout << s << "\n"; // 12
  cout << r << "\n"; // 10


}