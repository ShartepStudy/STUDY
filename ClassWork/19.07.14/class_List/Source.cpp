#include <iostream>
using namespace std;

struct Element
{
   char data;
   Element* Next;
};

class List
{
   Element* Head;
   Element* Tail;
   int Count;

public:
   List( )
   {
      Head = Tail = NULL;
      Count = 0;
   }

   void Add( char data )
   {
      Element * temp = new Element( );
      temp->data = data;
      temp->Next = NULL;
      if (Head==NULL)
      {
         Head = Tail = temp;
      }
      else
      {
         Tail->Next = temp;
         Tail = temp;
      }
   }

   void Del( )
   {
      Element* temp = Head;
      Head = Head->Next;
      delete temp;
   }

   void DelAll( )
   {
      while (Head != 0)
         Del( );
   }

   ~List( )
   {
      DelAll( );
   }

   void Print( )
   {
      Element * temp = Head;
      while (temp != 0)
      {
         cout << temp->data << " ";
         temp = temp->Next;
      }
      cout << "\n\n";
   }

   int GetCount( )
   {
      return Count;
   }
};

void main( )
{
   List lst;
   char*s = new char[200];
   strcpy( s, "Hello, world !!!\n\n" );
   cout<<s;
   int len = strlen( s );
   for (int i = 0; i < len; i++) lst.Add( s[i] );
   lst.Print( );
   lst.Del( );
   lst.Del( );
   lst.Del( );
   lst.Print( );
}
