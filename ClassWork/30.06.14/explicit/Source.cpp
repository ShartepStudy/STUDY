#include <iostream>
using namespace std;

class TFraction
{
	int mChis;
	int mZnam;
public:
	TFraction(): mChis(0), mZnam(1) {}
	TFraction(int c,int z): mChis(c), mZnam(z?z:1) {}
	explicit TFraction(int p): mChis(p), mZnam(1) {}

	void show() { cout << "chisl = " << mChis << "\tznam = " << mZnam << endl; }
};

void main()
{
	TFraction f;
	TFraction x(2,5);
	TFraction s(4);

	f.show();
	x.show();
	s.show();
}