#include <iostream>
using namespace std;

class CHuman 
{
	int mAge;
	char * mName;
public:
	CHuman()
      : mAge(0)
      , mName(0)
	{
      cout << "Default ctor!" << endl;
   }
   CHuman(char * name, int age)
      : mName(0)
   {
      cout << "Ctor with param!" << endl;
      setAge(age);
      if (name && strlen(name) > 0)
         setName(name);
      else
         setName("ERROR name");
   }
   ~CHuman() 
   {
      cout << mName << " destroy! " << endl;
      if (mName) delete[] mName;
   }
   void setAge(int age) { mAge = age>0 && age<100 ? age : 18; }
	void setName(char * name) 
	{
		if (name && strlen(name) > 0)
		{
			if (mName) delete [] mName;
			mName = new char[strlen(name) + 1];
			strcpy(mName, name);
		}
	}
	int getAge() const { return mAge; }
	const char * getName() { return mName; }
};

void main()
{
   CHuman ar[] = {
      CHuman("Vova", 58),
      CHuman()
   };

   ar[1].setName("Vitya");

   cout << ar[0].getName() << endl;
   cout << ar[1].getName() << endl;

}