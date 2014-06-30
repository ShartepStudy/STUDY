#include <iostream>
using namespace std;

class TPoint
{
	int mX;
	int mY;
public:
	TPoint(int a,int b): mX(a), mY(b) {}

	void setX(int x) 
	{
		cout << this << endl;
		mX=x; 
	}
};

void main()
{
	TPoint f(10,15);
	TPoint r(22,33);

	cout << &f << endl;
	f.setX(25);
}