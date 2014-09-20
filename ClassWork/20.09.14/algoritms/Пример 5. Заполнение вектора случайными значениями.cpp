#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int rangeRand()
{
	return rand()%10;
}
int main()
{
	vector<int> a(10);
	generate(a.begin(), a.end(),rangeRand);
	ostream_iterator<int> out(cout, " ");
	copy(a.begin(),a.end(), out); 
	cout << endl;
	return 0;
}
