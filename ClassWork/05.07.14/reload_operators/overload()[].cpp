#include <iostream>
using namespace std;

class Point{
	int X;
	int Y;
public:
	Point():X(0),Y(0){}
	Point(int X, int Y):X(X),Y(Y){}
	
	int& operator [](unsigned int field_number){
		return field_number==1?Y:X;
	}

	void operator ()(int newX, int newY){ // только в виде метода класса!
		X=newX;
		Y=newY;
	}
	void operator ()(int newValue){ // версий перегрузки может быть сколько угодно
		X=newValue;
		Y=newValue;
	}
};

//void main(){
//	Point obj;
//	cout<<obj[0]<<" - "<<obj[1]<<"\n";
//	//cout<<obj[-1]<<" - "<<obj[73]<<"\n";
//
//	Point p(5,10);
//	cout<<p[0]<<" - "<<p[1]<<"\n";
//
//	p[0]=3;
//	p[1]=7;
//	cout<<p[0]<<" - "<<p[1]<<"\n";
//
//	/////////////////////////////
//
//	p(33,44);
//	cout<<p[0]<<" - "<<p[1]<<"\n";
//
//	p(11);
//	cout<<p[0]<<" - "<<p[1]<<"\n";
//}