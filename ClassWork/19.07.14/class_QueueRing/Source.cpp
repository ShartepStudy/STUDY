#include <iostream>
#include <time.h>
using namespace std;

class QueueRing
{
   int* mass;
   int max_length;
   int current_length;

public:
   QueueRing( int m )
   {
      max_length = m;
      mass = new int[max_length];
      current_length = 0;
   }

   ~QueueRing( )
   {
      delete[]mass;
   }

   void Clear( )
   {
      current_length = 0;
   }

   bool IsEmpty( )
   {
      return current_length == 0;
   }

   bool IsFull( )
   {
      return current_length == max_length;
   }

   int GetCount( )
   {
      return current_length;
   }

   void Add( int digit )
   {
      if (!IsFull())
         mass[current_length++] = digit;
   }

   int Extract( )
   {
      if (!IsEmpty( ))
      {
         int first = mass[0];
         for (int i = 1; i<current_length; i++) mass[i-1] = mass[i];
         mass[current_length-1] = first;
         return 1;
      }
      else
         return 0;
   }

   void Show( )
   {
      cout<<"-----------------------------------\n";
      for (int i = 0; i<current_length; i++)
      {
         cout<<mass[i]<<"  ";
      }
      cout<<"\n";
      cout<<"-----------------------------------\n";
   }
};

void main( )
{
   srand( time( 0 ) );

   QueueRing q( 25 );

   for (int i = 0; i<5; i++) q.Add( rand( )%90+10 );

   q.Show( );

   q.Extract( );

   q.Show( );

   for (int i = 0; i<2; i++) q.Add( rand( )%90+10 );

   q.Show( );

   for (int i = 0; i<3; i++) q.Extract( );

   q.Show( );
}