#include <iostream>
#include <time.h>
using namespace std;

class QueuePriority
{
   int* mass;
   int* pr;
   int max_length;
   int current_length;

public:
   QueuePriority( int m )
   {
      max_length = m;
      mass = new int[max_length];
      pr = new int[max_length];
      current_length = 0;
   }

   ~QueuePriority( )
   {
      delete[]mass;
      delete[]pr;
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

   void Add( int digit, int p )
   {
      if (!IsFull())
      {
         mass[current_length] = digit;
         pr[current_length] = p;
         current_length++;
      }
   }

   int Extract( )
   {

      if (!IsEmpty( ))
      {
         int max_pr = pr[0];
         int max_pr_pos = 0;

         for (int i = 1; i<current_length; i++)
         {
            if (max_pr < pr[i])
            {
               max_pr = pr[i];
               max_pr_pos = i;
            }
         }

         int value = mass[max_pr_pos];

         for (int i = max_pr_pos; i<current_length-1; i++)
         {
            mass[i] = mass[i+1];
            pr[i] = pr[i+1];
         }

         current_length--;
         return  value;
      }
      else return -1;
   }

   void Show( )
   {
      cout<<"-----------------------------------\n";
      for (int i = 0; i<current_length; i++)
      {
         cout<<mass[i]<<" - "<<pr[i]<<"\n";
      }
      cout<<"\n";
      cout<<"-----------------------------------\n";
   }
};

void main( )
{
   srand( time( 0 ) );

   QueuePriority q( 25 );

   q.Add( 10, 1 );
   q.Add( 8, 2 );
   q.Add( 6, 3 );
   q.Add( 4, 4 );
   q.Add( 2, 5 );

   q.Extract( );
   q.Extract( );
   q.Extract( );
   q.Extract( );

   q.Show( );
}