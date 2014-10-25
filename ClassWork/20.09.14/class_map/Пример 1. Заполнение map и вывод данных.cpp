#include <iostream>
#include <string>
#include <map>
using namespace std;

//��� ���������� ������ ������ �����������:
typedef map<int,string> MyMap;
typedef MyMap::iterator Iter;
int main()
{
	//��������� ������������� map
	MyMap m;
	//������������� value_type ��� ������������ ���� "���� - ��������"
	m.insert(MyMap::value_type(1,"Ivanov"));
	//����� ��������������� ������������ ��� pair
	m.insert(pair<int,string>(2,"Petrov"));
	//������������� ������� make_pair
	m.insert(make_pair(3,"Sidorov"));


	for(auto x: m)
	{
		//������������� ������� ���������:
		//first ��� ��������� � �����,
		//second ��� ��������� � ��������
		cout << x.first << " " << x.second << endl;
	}
	
	return 0;
}
