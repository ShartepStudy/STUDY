#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main()
{
	//�������� �������, ����������� 3 �������� �� ��������� 0
	vector<int> a(3, 0);
	int ar[4] = {1,2,3,4};
   //�������� �������, ����������� 3 ������ �������� �������
	vector<int> b(ar, ar+3);
   //�������� ����� ������� b
	vector<int> c(b);

	//�����  ��������
	ostream_iterator<int, char> out(cout," _ ");
	cout << "Vector a: "; 
	copy(a.begin(), a.end(), out); 
	cout << endl;
	cout << "Vector b: "; 
	copy(b.rbegin(), b.rend(), out); 
	cout << endl;
	cout << "Vector c: "; 
	copy(c.begin(), c.end(), out); 
	cout << endl;
	return 0;
}
