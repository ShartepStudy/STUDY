#include <stack>
#include <iostream>
using namespace std;

void main( )
{
	
	stack <int> s1, s2;

	s1.push( 10 );//добавляет элемент в вершину стека
	s1.push( 20 );
	s1.push( 30 );

	stack <int>::size_type i;
	i = s1.size( ); //возвращает количество элементов в стеке
	cout << "The stack length is " << i << "." << endl;

	i = s1.top( ); //возвращает ссылку на элемент в вершине стека
	cout << "The element at the top of the stack is "
		<< i << "." << endl;

	s1.pop( );//удаляет элемент из вершины стека

	i = s1.size( );
	cout << "After a pop, the stack length is " 
		<< i << "." << endl;

	i = s1.top( );
	cout << "After a pop, the element at the top of the stack is "
		<< i << "." << endl;

	if ( s1.empty( ) )//проверяет, пустой ли стек
		cout << "The stack s1 is empty." << endl;
	else
		cout << "The stack s1 is not empty." << endl;

	if ( s2.empty( ) )
		cout << "The stack s2 is empty." << endl;
	else
		cout << "The stack s2 is not empty." << endl;

}