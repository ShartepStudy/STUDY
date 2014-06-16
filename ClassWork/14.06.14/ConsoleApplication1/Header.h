
class CTest
{
private:
   int x;
   int y;
public:
   CTest();
   void show();
};

CTest::CTest() 
   : x(0)
   , y(0)
{};

void CTest::show()
{
   cout << x << endl;
   cout << y << endl;
}