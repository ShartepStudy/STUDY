#include <vector>
#include <iostream>

using namespace std;
int main()
{
	int a[3] = {1,2,3};
	vector<int> b;

	//������������� ��������� ��� ������ ��������� �������
	int * pa;
	for(pa = a; pa < a + 3; pa++)//pricvainie pa adres nylevogo elementa a, pricvaivaem a znachenie +1, +2, +3 
		cout << *pa << " ";
	cout << endl;

	for(int i = 0; i < 3; i++) b.push_back(i+1);
    
	//������������� ��������� ��� ������ ��������� �������
//	vector<int>::iterator pb;
	for(auto pb = b.rbegin(); pb != b.rend(); pb++)//metod begin vozrawaet adres 0-elementa
		cout << *pb << " ";
	cout << endl;

	return 0;
}
