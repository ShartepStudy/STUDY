#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

//создание собственного функционального объекта для возведения числа в степень
//наследование от binary_function для определения типов аргументов и типа результата
template <class Arg1, class Arg2>
struct MyPower: public binary_function<Arg1, Arg2, Arg1>
{
	Arg1 operator()(Arg1 a, Arg2 b)const {return pow(a,b);}
} ;

int main()
{
	int ar[] = {2,5,7};
	
	vector<int> a = vector<int>(ar, ar+3);
	
	ostream_iterator<int> out(cout, " "); 
	cout << "Initial state: "; 
	copy(a.begin(),a.end(),out); 
	cout << endl;

	//использование функционального адаптера с собственным функтором:
    //для вывода квадратов элементов
	cout << "vector elements in power 2: "; 
	transform(a.begin(),a.end(),out,bind2nd(MyPower<float, int>(),2));
	cout << endl;

	//использование функционального адаптера с собственным функтором:
	//для возведения 2 в степень, равную элементам массива
	cout << "2 in power of vecot elements: "; 
	transform(a.begin(),a.end(),out,bind1st(MyPower<float,int>(),2));
	cout << endl;

	return 0;
}
