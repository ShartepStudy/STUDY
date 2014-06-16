#include "Group.h"

void CGroup::initGroup( int count )
{
   vector<string> menFamily;
   vector<string> womenFamily;
   vector<string> menNames;
   vector<string> womenNames;
   vector<string> menSecondNames;
   vector<string> womenSecondNames;

   vector<string> * nameArrays[6] = { &womenFamily, &menFamily, &menNames, &womenNames, &menSecondNames, &womenSecondNames };
   string fileNames[6] = { "womenFamily.txt", "menFamily.txt", "manNames.txt", "womenNames.txt", "manSecondNames.txt", "womenSecondNames.txt" };

   for (size_t i = 0; i < 6; i++)
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

   for (size_t i = 0; i < count; i++)
   {
      bool isMale = rand()%2;
      vector<string> & family = isMale ? menFamily : womenFamily;
      vector<string> & name = isMale ? menNames : womenNames;
      vector<string> & secondName = isMale ? menSecondNames : womenSecondNames;

      string birthday;
      char str[5];
      birthday += itoa( rand()%30, str, 10 );
      birthday += '.';
      birthday += itoa( rand()%13+1, str, 10 );
      birthday += '.';
      birthday += itoa( rand()%15+1998, str, 10 );

      string phone = "+38";
      for (size_t i = 0; i < 9; i++)
         phone += 48 + rand()%10;

      CStudent student( family[rand()%family.size()]
         , name[rand()%name.size()]
         , secondName[rand()%secondName.size()]
         , birthday
         , "Test adress"
         , phone );
      addStudent( student );
   }
}

void CGroup::removeStudent( int index )
{
   mArray.erase( mArray.begin()+index );
}

CGroup::CGroup()
   : mName( "TestGroup-30" )
   , mSpecialty( "TestSpecialty-30" )
   , mNumber( rand()%9999+1 )
   , mSize(0)
{
   initGroup( 30 );
}

CGroup::CGroup( int size ) 
   : mName( "TestGroup-sized" )
   , mSpecialty( "TestSpecialty-sized" )
   , mNumber( rand()%9999+1 )
   , mSize( 0 )
{
   initGroup( size );
}

CGroup::CGroup( CStudent * studentArray, int size ) 
   : mName( "TestGroup-studentArray" )
   , mSpecialty( "TestSpecialty-studentArray" )
   , mNumber( rand()%9999+1 )
   , mSize( 0 )
{
   for (int i = 0; i < size; i++)
      addStudent( studentArray[i] );
}

CGroup::CGroup( CGroup & group ) 
   : mName( group.mName )
   , mSpecialty( group.mSpecialty )
   , mNumber( group.mNumber )
   , mSize( group.mSize )
   , mArray( group.mArray )
{}

void CGroup::showGroup() 
{
   cout << "Group name: " << mName << endl;
   cout << "Group specialty: " << mSpecialty << endl;
   cout << "Group number: " << mNumber << endl;

   for (size_t i = 0; i < mSize; i++)
      cout << i << '\t' << mArray[i].getFamilyName() << ' ' << mArray[i].getName() << ' ' << mArray[i].getSecondName() << endl;
   cout << endl;
}

void CGroup::addStudent( CStudent & student )
{
   mArray.push_back( student );
   sort( mArray.begin(), mArray.end(), sortFamilyName );
   mSize++;
}

CStudent & CGroup::editStudent( int index ) 
{ 
   return mArray[index]; 
}

void CGroup::setGroupName( string name ) { mName = name; }
void CGroup::setGroupSpecialty( string specialty ) { mSpecialty = specialty; }
void CGroup::setGroupNamber( int number ) { mNumber = number; }

void CGroup::moveStudentToOtherGroup( int studentNumber, CGroup & group ) 
{
   group.addStudent( mArray[studentNumber] );
   removeStudent( studentNumber );
}

void CGroup::allocationBadStudents() 
{
   for (int i = 1; i < mSize; i++)
      if ( !mArray[i].isPassSession() )
         removeStudent( i );
}

void CGroup::allocationWorstStudent() 
{
   int index = 0;
   int minRating = mArray[0].getRating();

   for (int i = 1; i < mSize; i++)
   {
      int tmpRating = mArray[i].getRating();
      if (minRating>tmpRating)
      {
         minRating = tmpRating;
         index = i;
      }
   }

   removeStudent( index );
}