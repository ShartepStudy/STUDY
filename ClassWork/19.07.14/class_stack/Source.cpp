
#include <iostream>
#include <time.h>
using namespace std;

class Stack
{
   enum { SIZE = 10, EMPTY = 0 };
   int mass[SIZE];
   int top; // индекс вершины стека

public:
   Stack( )
   {
      top = EMPTY;
   }

   void Clear( )
   {
      top = EMPTY;
   }

   bool IsEmpty( )
   {
      return top == EMPTY;
   }

   bool IsFull( )
   {
      return top == SIZE;
   }

   int GetCount( )
   {
      return top;
   }

   void Push( int digit )
   {
      if (!IsFull())
         mass[top++] = digit;
   }

   int Pop( )
   {
      if (!IsEmpty())
         return mass[--top];
      else 
         return 0;
   }
};

void main( )
{
   srand( time( 0 ) );
   Stack st;

   while (!st.IsFull())
      st.Push( rand( )%90+10 );

   while (!st.IsEmpty())
      cout<<st.Pop( )<<"  ";

   Stack test;
   test.Pop();
   cout<<"\n\n";
}