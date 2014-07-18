#include <iostream>
using namespace std;

class Test
{
	int t;

public:
	Test()
	{
		cout << "конструктор: создание объекта типа Test\n";
		t = 25;
	}
	void Show()
	{
		cout << t << "\n";
	} 
	void Set(int t)
	{
		this->t = t;
	}

	friend ostream& operator << (ostream& os, Test obj);
	friend istream& operator >> (istream& is, Test obj);
};

ostream& operator << (ostream& os, Test obj)
{
	os << obj.t << "\n";
	return os;
}

istream& operator >> (istream& is, Test obj)
{
	is >> obj.t;
	return is;
}

class MyPtr
{
	Test* ptr;

public:
	MyPtr (Test* p = NULL)
	{
		cout<<"конструктор: создание указателя на объект типа Test\n";
		ptr = p;
	}

	Test * operator->()
	{
		return ptr;
	}

	Test & operator*()
	{
		cout<<"разыменование указателя\n";
		return *ptr;
	}

	MyPtr& operator ++ ()
	{
		cout<<"префиксная форма ++\n";
		ptr++;
		return *this;
	}

	MyPtr& operator ++ (int k)
	{
		cout<<"постфиксная форма ++\n";
		MyPtr t;
		t.ptr = ptr;
		ptr++;
		return t;
	}

	MyPtr& operator -- ()
	{
		cout<<"префиксная форма --\n";
		ptr--;
		return *this;
	}

	MyPtr& operator -- (int k){
		cout<<"постфиксная форма --\n";
		MyPtr t;
		t.ptr = ptr;
		ptr--;
		return t;
	}

	operator Test*()
	{
		cout<<"преобразование к типу MyPtr\n";
		return ptr;
	}

	friend MyPtr& operator + (int d, const MyPtr p);
	friend MyPtr& operator + (const MyPtr& p, int d);
	friend MyPtr& operator - (const MyPtr& p, int d);

	friend MyPtr& operator += (const MyPtr& p, int d);
	friend MyPtr& operator -= (const MyPtr& p, int d);
};

MyPtr& operator + (int d, const MyPtr p)
{
	MyPtr temp;
	temp.ptr = d + p.ptr;
	return temp;
}

MyPtr& operator + (const MyPtr& p, int d)
{
	MyPtr temp;
	temp.ptr = p.ptr + d;
	return temp;
}

MyPtr& operator - (const MyPtr& p, int d)
{
	MyPtr temp;
	temp.ptr = p.ptr - d;
	return temp;
}

MyPtr& operator += (const MyPtr& p, int d)
{
	MyPtr temp;
	temp.ptr = p.ptr + d;
	return temp;
}

MyPtr& operator -= (const MyPtr& p, int d)
{
	MyPtr temp;
	temp.ptr = p.ptr - d;
	return temp;
}

void main ()
{
	setlocale(0,"");

	Test* obj = new Test;

	obj->Show();

	/////////////////////////////

	MyPtr p(obj);

	p->Show();

	cout<< *p;

	delete p;

	/////////////////////////////

	Test* mass = new Test[5];
	for(int i=0; i<5;i++)
	{
		mass[i].Set(i);
		mass[i].Show();
	}

	MyPtr pm = mass;

	pm++;
	++pm;
	pm--;
	--pm;
	pm -= 2;
	pm += 2;

	cout << *pm;

	delete[] mass;
}