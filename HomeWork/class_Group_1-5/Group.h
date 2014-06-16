#if !defined (_C_GROUP_H)
#define _C_GROUP_H

#include "Student.h"
#include <algorithm>
#include <fstream>
#include <time.h>
#include <Windows.h>


class CGroup
{
private:
   vector<CStudent> mArray;
   short mSize;
   string mName;
   string mSpecialty;
   short mNumber;

   struct sortPredicateFamilyName
   {
      bool operator() ( CStudent & s1, CStudent & s2 )
      {
         return (s1.getFamilyName()<s2.getFamilyName());
      }
   } sortFamilyName;

   void initGroup( int count );
   void removeStudent( int index );  
public:
   CGroup();
   CGroup(int size);
   CGroup(CStudent * studentArray, int size);
   CGroup( CGroup & group );

   void showGroup();
   void addStudent( CStudent & student );
   CStudent & editStudent( int index );

   void setGroupName( string name );
   void setGroupSpecialty( string specialty );
   void setGroupNamber( int number );

   void moveStudentToOtherGroup( int studentNumber, CGroup & group );
   void allocationBadStudents();
   void allocationWorstStudent();
};

#endif
