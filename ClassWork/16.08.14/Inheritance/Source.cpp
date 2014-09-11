#include <iostream>
using namespace std;

// Класс "точка"
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
   // получение x
   int& GetX()
   {
      return x;
   }
   // получение y
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
   // получение ширины
   int& GetWidth()
   {
      return width;
   }
   // получение высоты
   int& GetHeight()
   {
      return height;
   }
   // функции сдвига
   void MoveX(int DX)
   {
      x += DX;
   }
   void MoveY(int DY)
   {
      y = DY;
   }
   // показ на экран
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
   //// создание объекта
   //MyWindow A(10, 20);
   //A.Show();
   //// изменение параметров
   //A.GetX() = 5;
   //A.GetY() = 3;
   //A.GetWidth() = 40;
   //A.GetHeight() = 50;
   //A.Show();

   //// сдвиг "окна"
   //A.MoveX(2);
   //A.MoveY(7);
   //A.Show();

   MyWindow A(10, 20);

}