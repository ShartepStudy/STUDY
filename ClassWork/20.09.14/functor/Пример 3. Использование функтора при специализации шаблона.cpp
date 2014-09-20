#include <iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

//�����, ����������� �����
class Book
{
public:
	string subject; //���������� �������
	string theme;   //����
	string name;    //��������
	Book(string iSubject, string iTheme, string iName): subject(iSubject), theme(iTheme), name(iName){}
};

//�������, ������������ ��� ������� �������� ������������ ����������
class cmpBooks
{
 public:
	   //�������� () ������������ ��� ��������� ���� �� ������� ������
       //� � �������� ����� ������� ������ �� ��������
	bool operator() (const Book& a, const Book& b) 
	{
		if (a.subject == b.subject)	return a.theme < b.theme;
 		 return (a.subject < b.subject);
	}
};

// ������� ��������� (�� ����� ���� ������������ � �������� �������� ���������� ���������)
bool cmpBooksFunc(const Book& a, const Book& b)
{
	if (a.subject == b.subject)	return a.theme < b.theme;
 		 return (a.subject < b.subject);
}

//������!!! - ������� �� ����� �������������� � �������� �������� ��������� ������� 
//typedef set<Book, cmpBooksFunc> setBooks;

//������� - ����� �������������� � �������� �������� ��������� ������� 
typedef set<Book, cmpBooks> setBooks;

int main()
{
	setBooks b; //��������� ����
	//���������� ����
	b.insert(Book("Nature","Ocean","The Pacific"));
	b.insert(Book("Technics","Harware","PC"));
	b.insert(Book("Nature","Animals","Sheathbill"));
	
	//����� ����
	setBooks::iterator it;
      for(it = b.begin(); it != b.end(); it++)
    	 cout << (*it).subject << " " << (*it).theme << " " <<(*it).name << endl;
	
	return 0;
}
