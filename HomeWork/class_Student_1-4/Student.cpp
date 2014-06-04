#include "Student.h"

CStudent::CStudent()
{}

CStudent::CStudent( string familyName, string name, string secondName )
   : mFamilyName( familyName )
   , mName( name )
   , mSecondName( secondName )
{}

CStudent::CStudent( string familyName, string name, string secondName, string birthday )
   : mFamilyName( familyName )
   , mName( name )
   , mSecondName( secondName )
   , mBirthday( birthday )
{}

CStudent::CStudent( string familyName, string name, string secondName, string birthday, string adress, string phone )
   : mFamilyName( familyName )
   , mName( name )
   , mSecondName( secondName )
   , mBirthday( birthday )
   , mAdress( adress )
   , mPhone( phone )
{}

CStudent::~CStudent() 
{}

void CStudent::showData()
{
   cout << "Student Name: " << mFamilyName << ' ' << mName << ' ' << mSecondName << endl;
   cout << "Adress: " << mAdress << endl;
   cout << "Phone: " << mPhone << endl;
   cout << "Birthday: " << mBirthday << endl;

   cout << "Zachet marks: \t\t";
   for (size_t i = 0; i < mZachet.size(); i++)
      cout << mZachet[i] << '\t';

   cout << endl << "Coursework marks: \t";
   for (size_t i = 0; i < mCoursework.size(); i++)
      cout << mCoursework[i] << '\t';

   cout << endl << "Exam marks: \t\t";
   for (size_t i = 0; i < mExam.size(); i++)
      cout << mExam[i] << '\t';

   cout << endl << endl;
}

const string & CStudent::getFamilyName() { return mFamilyName; }
const string & CStudent::getName() { return mName; }
const string & CStudent::getSecondName() { return mSecondName; }
const string & CStudent::getBirthday() { return mBirthday; }
const string & CStudent::getAdress() { return mAdress; }
const string & CStudent::getPhone() { return mPhone; }
short CStudent::getZachetMark( short index ) { return mZachet[index]; }
short CStudent::getCourseworkMark( short index ) { return mCoursework[index]; }
short CStudent::getExamMark( short index ) { return mExam[index]; }

void CStudent::setFamilyName( string familyName ) { mFamilyName = familyName; }
void CStudent::setName( string name ) { mName = name; }
void CStudent::setSecondName( string secondName ) { mSecondName = secondName; }
void CStudent::setBirthday( string birthday ) { mBirthday = birthday; }
void CStudent::setAdress( string adress ) { mAdress = adress; }
void CStudent::setPhone( string phone ) { mPhone = phone; }
void CStudent::setZachetMark( short index, short mark ) { mZachet[index] = mark; }
void CStudent::setCourseworkMark( short index, short mark ) { mCoursework[index] = mark; }
void CStudent::setExamMark( short index, short mark ) { mExam[index] = mark; }

void CStudent::addZachetMark( short mark ) { mZachet.push_back( mark ); }
void CStudent::addCourseworkMark( short mark ) { mCoursework.push_back( mark ); }
void CStudent::addExamMark( short mark ) { mExam.push_back( mark ); }

void CStudent::delZachetMark( short index ) { mZachet.erase(mZachet.begin()+index); }
void CStudent::delCourseworkMark( short index ) { mCoursework.erase( mCoursework.begin()+index ); }
void CStudent::delExamMark( short index ) { mCoursework.erase( mCoursework.begin()+index ); }

void CStudent::getAutoZachet() { mZachet.push_back( BEST_MARK ); }
void CStudent::getAutoCoursework() { mCoursework.push_back( BEST_MARK ); }
void CStudent::getAutoExam() { mExam.push_back( BEST_MARK ); }

void CStudent::oversleepZachet() { mZachet.push_back( WORST_MARK ); }
void CStudent::oversleepCoursework() { mCoursework.push_back( WORST_MARK ); }
void CStudent::oversleepExam() { mExam.push_back( WORST_MARK ); }

