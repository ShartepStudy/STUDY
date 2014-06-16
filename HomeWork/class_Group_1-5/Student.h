#if !defined (_C_STUDENT_H)
#define _C_STUDENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

const short BEST_MARK = 5;
const short WORST_MARK = 2;
const short RATING_FOR_PASS_SESSION = 2;

class CStudent
{
private:
   string mFamilyName;
   string mName;
   string mSecondName;
   string mBirthday;
   string mAdress;
   string mPhone;

   vector<short> mZachet;
   vector<short> mCoursework;
   vector<short> mExam;
public:
   CStudent();
   CStudent( string familyName, string name, string secondName );
   CStudent( string familyName, string name, string secondName, string birthday );
   CStudent( string familyName, string name, string secondName, string birthday, string adress, string phone );
   ~CStudent();

   void showData();

   const string & getFamilyName();
   const string & getName();
   const string & getSecondName();
   const string & getBirthday();
   const string & getAdress();
   const string & getPhone();
   short getZachetMark( short index );
   short getCourseworkMark( short index );
   short getExamMark( short index );
   int getRating();

   void setFamilyName( string  familyName );
   void setName( string name );
   void setSecondName( string secondName );
   void setBirthday( string birthday );
   void setAdress( string adress );
   void setPhone( string phone );
   void setZachetMark( short index, short mark );
   void setCourseworkMark( short index, short mark );
   void setExamMark( short index, short mark );

   void addZachetMark( short index );
   void addCourseworkMark( short index );
   void addExamMark( short index );

   void delZachetMark( short index );
   void delCourseworkMark( short index );
   void delExamMark( short index );

   void getAutoZachet();
   void getAutoCoursework();
   void getAutoExam();

   void oversleepZachet();
   void oversleepCoursework();
   void oversleepExam();

   bool isPassSession();
};

#endif
