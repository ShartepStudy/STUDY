#include <iostream>
using namespace std;

const double PI = 3.14159;

class Point
{
protected:
   double x;
   double y;
public:
   //Point()
   //{
   //   cout << "Point default c-tor!\n";
   //   x = y = 5;
   //}
   Point(int x, int y)
   {
      cout << "Point param c-tor!\n";
      this->x = x;
      this->y = y;
   }
   void ShowPoint()
   {
      cout << "Point - X: " << x << ", Y: " << y << "\n";
   }
   ~Point()
   {
      cout << "Point d-tor!\n";
   }
};

class Circle : virtual public Point
{
protected:
   double radius;
   double area;
public:
   Circle() : Point(0, 0)
   {
      cout << "Circle default c-tor!\n";
      radius = 5;
      area = PI * radius * radius;
   }
   Circle(int center_x, int center_y, int radius) :Point(center_x, center_y)
   {
      cout << "Circle param c-tor!\n";
      this->radius = radius;
   }
   void ShowCircle()
   {
      //cout<<x<<" "<<y<<" "<<radius<<"\n";
   }
   ~Circle()
   {
      cout << "Circle d-tor!\n";
   }
};

class Rect : virtual public Point
{
protected:
   double x2;
   double y2;
   double area;
public:
   Rect() : Point(0,0)
   {
      cout << "Rect c-tor!\n";
      x2 = y2 = 10;
      area = (x2 - x) * (x2 - x);
   }
   void ShowRect()
   {
      //cout<<x<<" "<<y<<" "<<x2<<" "<<y2<<"\n";
   }
   ~Rect()
   {
      cout << "Rect d-tor!\n";
   }
};

class CircleInTheRect : public Circle, public Rect
{
   double exclusive_area;
public:
   CircleInTheRect() : Point(3, 2)
   {
      cout << "CircleInTheRect c-tor!\n";
      //exclusive_area = area - area;
      //exclusive_area = Rect::area - Circle::area;
   }
   void ShowCircleInTheRect()
   {
      //cout<<x<<" "<<y<<" "<<x2<<" "<<y2<<"\n";
      //cout<<Rect::x<<" "<<Rect::y<<" "<<x2<<" "<<y2<<"\n";
   }
   ~CircleInTheRect()
   {
      cout << "CircleInTheRect d-tor!\n";
   }
};

void main()
{
   //Point obj1;
   //obj1.ShowPoint();

   //Circle obj2;
   //obj2.ShowCircle();

   //Rect obj3;
   //obj3.ShowRect();

   CircleInTheRect obj4;
   obj4.ShowCircleInTheRect();
}