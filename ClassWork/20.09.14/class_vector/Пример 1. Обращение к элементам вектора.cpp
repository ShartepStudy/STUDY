#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int main()
{
	//создание пустого вектора
	vector<int> a;
	
  cout << a.size() << endl;
  //заполнение вектора элементами
	for(int i = 0; i < 10; i++)
    a.push_back(i);

  cout << a.size() << endl;

	//вывод  векторов с помощью индексов
	for(int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;

	//обращение по недопустимому индексу
	try
	{
	  //cout << a[11] << endl; //эта строка приводит к возникновению ошибки
                                 //времени выполнения
	    cout << a.at(11) << endl;//эта строка приводит к возникновению 
                                   // исключения, которое перехватывается обработчиком
	}
	catch(out_of_range e)
	{
		cout << e.what() << endl;
	}
  return 0;
}
