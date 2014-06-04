#include <time.h>
#include "Student.h"


void main()
{
   srand( (int) time( NULL ) );

   CStudent s1;
   CStudent s2( "Petrash", "Oleksandr", "Sergeevich" );
   CStudent s3( "Ivanov", "Ivan", "Ivanovich", "25.03.1973" );
   CStudent s4( "Petrov", "Petr", "Petrovich", "05.03.1973", "Ukraine, Odessa", "+380506749465" );

   for (size_t i = 0; i < 5; i++)
   {
      s4.addZachetMark( rand()%4+2 );
      s4.addCourseworkMark( rand()%4+2 );
      s4.addExamMark( rand()%4+2 );
   }

   
   s1.setName("Vasya");

   s1.showData();
   s2.showData();
   s3.showData();
   s4.showData();
}

