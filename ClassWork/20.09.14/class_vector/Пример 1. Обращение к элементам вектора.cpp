#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int main()
{
	//�������� ������� �������
	vector<int> a;
	
  cout << a.size() << endl;
  //���������� ������� ����������
	for(int i = 0; i < 10; i++)
    a.push_back(i);

  cout << a.size() << endl;

	//�����  �������� � ������� ��������
	for(int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;

	//��������� �� ������������� �������
	try
	{
	  //cout << a[11] << endl; //��� ������ �������� � ������������� ������
                                 //������� ����������
	    cout << a.at(11) << endl;//��� ������ �������� � ������������� 
                                   // ����������, ������� ��������������� ������������
	}
	catch(out_of_range e)
	{
		cout << e.what() << endl;
	}
  return 0;
}
