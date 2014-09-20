#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int ar[] = {1,-2,3,-4,5,-6,7,-8};
	vector<int> a(ar, ar+8);
	cout << "Initial state: ";
	ostream_iterator<int> out(cout, " ");
	copy(a.begin(),a.end(), out); cout << endl;

	//изменение знака каждого элемента на противоположный
	transform(a.begin(), a.end(), a.begin(), negate<int>());
	cout << "Reverse sign: ";
	copy(a.begin(),a.end(), out); cout << endl;
 
	//попарное перемножение элементов вектора и массива
	cout << "Sum of vector and array: ";
	transform(a.begin(), a.end(), ar, out, multiplies<int>());
	cout << endl;
	return 0;
}
