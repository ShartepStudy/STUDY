#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int ar[] = {1,1,2,2,3,3,3};
	vector<int> a(ar, ar + 6);
	cout << "Initial state: "; 
	ostream_iterator<int> out(cout, " ");
	copy(a.begin(),a.end(), out); 
	cout << endl;
	
	// �������� ������� ����� ��������, 
	// ����������� ��������� end() �� ����� ����� �������
	a.erase(unique(a.begin(),a.end()), a.end());
	cout << "Atfer remove duplicates: "; 
	copy(a.begin(),a.end(), out); 
	cout << endl;
	
	return 0;
}
