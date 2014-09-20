#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // задание векторов
	int ar[] = {20,30,40};
	int br[] = {1,2,3};
	vector<int> a = vector<int>(ar, ar+3);
	vector<int> b = vector<int>(br, br+3);
	ostream_iterator<int> out(cout, " "); 
	cout << "a: "; 
	copy(a.begin(),a.end(),out);
	cout << endl;
	cout << "b: "; 
	copy(b.begin(),b.end(),out); 
	cout << endl;
    // использование функторов дл€ выполнени€ попарного сложени€ элементов векторов
	cout << "use plus<int>(): ";
	transform(a.begin(), a.end(), b.begin(), out, plus<int>()); 
	cout << endl;
    // использование функторов дл€ выполнени€ попарного вычитани€ элементов векторов
    cout << "use minus<int>(): ";
	transform(a.begin(), a.end(), b.begin(), out, minus<int>());  
	cout << endl;
    // использование функторов дл€ выполнени€ попарного делени€ элементов векторов
	cout << "use devides<int>(): ";
	transform(a.begin(), a.end(), b.begin(), out, divides<int>());  
	cout << endl;
    // использование функторов дл€ выполнени€ попарного умножени€ элементов векторов
	cout << "use multiplies<int>(): ";
	transform(a.begin(), a.end(), b.begin(), out, multiplies<int>());  
	cout << endl;
	
	return 0;
}
