#include "Group.h"


CGroup::CGroup()
   : mName( "TestGroup" )
   , mSpecialty( "TestSpecialty" )
   , mNumber( rand()%9999+1 )
   , mSize(0)
{
   vector<string> family;
   vector<string> menNames;
   vector<string> womenNames;
   vector<string> menSecondNames;
   vector<string> womenSecondNames;

   vector<string> * nameArrays[5] = { &family, &menNames, &womenNames, &menSecondNames, &womenSecondNames };
   string fileNames[5] = { "Family.txt", "manNames.txt", "womenNames.txt", "manSecondNames.txt", "womenSecondNames.txt" };

   for (size_t i = 0; i < 5; i++)
   {
      ifstream file( fileNames[i] );
      while (!file.eof())
      {
         char str[100];
         file.getline( str, 100 );
         nameArrays[i]->push_back( str );
      }
      file.close();
   }

   srand( (int) time( NULL ) );

   for (size_t i = 0; i < 30; i++)
   {
      vector<string> & name = rand()%2 ? menNames : womenNames;
      vector<string> & secondName = rand()%2 ? menSecondNames : womenSecondNames;

      string birthday;
      char str[5];
      itoa( rand()%30, str, 10 );
      birthday += str;
      birthday += '.'; 
      itoa( rand()%13+1, str, 10 );
      birthday += str;
      birthday += '.';
      itoa( rand()%15+1998, str, 10 );
      birthday += str;

      string phone = "+38";
      for (size_t i = 0; i < 9; i++)
         phone += 48 + rand()%10;

      CStudent student( family[ rand()%family.size() ]
                        , name[ rand()%name.size() ]
                        , secondName[ rand()%secondName.size() ]
                        , birthday
                        , "Test adress"
                        ,  phone);
      addStudent( student );
   }
}

CGroup::CGroup( int size ) {};
CGroup::CGroup( CStudent * studentArray, int size ) {};
CGroup::CGroup( CGroup & group ) {};

void CGroup::showGroup() 
{
   cout << "Group name: " << mName << endl;
   cout << "Group specialty: " << mSpecialty << endl;
   cout << "Group number: " << mNumber << endl;

   for (size_t i = 0; i < mSize; i++)
      cout << i << '\t' << mArray[i].getFamilyName() << ' ' << mArray[i].getName() << ' ' << mArray[i].getSecondName() << endl;
   cout << endl;
}

void CGroup::addStudent( CStudent student )
{
   mArray.push_back( student );
   sort( mArray.begin(), mArray.end(), sortFamilyName );
   mSize++;
}

CStudent & CGroup::editStudent( int index ) 
{ 
   return mArray[index]; 
}

void CGroup::setGroupName( string name ) {};
void CGroup::setGroupSpecialty( string specialty ) {};
void CGroup::setGroupNamber( int number ) {};

void CGroup::moveStudentToOtherGroup( int studentNumber, CGroup & group ) {};
void CGroup::allocationBadStudents() {};
void CGroup::allocationWorstStudent() {};