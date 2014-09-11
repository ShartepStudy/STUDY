#include <iostream>
using namespace std;

// ����� "�����"
class Point
{
protected:
   int x;
   int y;
public:
   Point()
   {
      x = 0;
      y = 0;
      cout << "Def c-tor Point!\n";
   }
   // ��������� x
   int& GetX()
   {
      return x;
   }
   // ��������� y
   int& GetY()
   {
      return y;
   }
};

class MyWindow : public Point
{
   int width;
   int height;
public:
   MyWindow(int W, int H)
   {
      width = W;
      height = H;
      cout << "Param c-tor Window!\n";
   }
   // ��������� ������
   int& GetWidth()
   {
      return width;
   }
   // ��������� ������
   int& GetHeight()
   {
      return height;
   }
   // ������� ������
   void MoveX(int DX)
   {
      x += DX;
   }
   void MoveY(int DY)
   {
      y = DY;
   }
   // ����� �� �����
   void Show()
   {
      cout << "--------------\n\n";
      cout << "X = " << x << "\n\n";
      cout << "Y = " << y << "\n\n";
      cout << "W = " << width << "\n\n";
      cout << "H = " << height << "\n\n";
      cout << "--------------\n\n";
   }
};
void main()
{
   //// �������� �������
   //MyWindow A(10, 20);
   //A.Show();
   //// ��������� ����������
   //A.GetX() = 5;
   //A.GetY() = 3;
   //A.GetWidth() = 40;
   //A.GetHeight() = 50;
   //A.Show();

   //// ����� "����"
   //A.MoveX(2);
   //A.MoveY(7);
   //A.Show();

   MyWindow A(10, 20);

}