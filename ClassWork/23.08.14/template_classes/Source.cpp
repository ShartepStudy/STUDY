template <class T> 
class Pair
{
   T a;
   T b;
public:
   Pair(T t1, T t2) : a(t1), b(t2) {}
};


template <class T>
class Trio : public Pair<T>
{
   T c;
public:
   Trio(T t1, T t2, T t3) : Pair<T>(t1, t2), c(t3)
   {}
};

class Point
{
public:
  int x_;
  int y_;

  Point(int x, int y) : x_(x), y_(y) {}
};

template <typename T>
class Point3D : public Point {
public:
  T z_;
  Point3D(int x, int y, T z) : Point(x, y), z_(z) {}
};

class Circle : public Point3D<double> {
public:
  int area;
  Circle(int x, int y, double z) : Point3D<double>(x, y, z), area(0) {}
};

void main()
{
   int a = 5, b = 6;
   Pair<int*> bb(&a, &b);

  
   Pair<Pair<int> > c(Pair<int> (4, 5), Pair<int> (8,9));
}