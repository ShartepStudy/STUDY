#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;

class Point
{
public:

   int X;
   int Y;

   Point()
   {
      X = Y = 0;
   }
   void SetPoint(int iX, int iY)
   {
      X = iX;
      Y = iY;
   }
};

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

class Figura
{
   Point*obj;
   int count;
   int rc, gc, bc;
public:
   Figura()
   {
      count = 0;
      obj = NULL;
   }
   void CreateFigura(int p_count, int R, int G, int B)
   {
      if (p_count<3) p_count = 3;
      count = p_count;
      rc = R; gc = G; bc = B;

      // выдделение памяти под массив точек
      obj = new Point[count];
      if (!obj) exit(0);

      for (int i = 0; i<count; i++)
      {
         obj[i].SetPoint(rand() % 600, rand() % 400);
      }
   }

   //показ фигуры
   void ShowFigura()
   {
      ReleaseDC(hwnd, hdc);
      hdc = GetDC(hwnd);
      HPEN pen = CreatePen(rand() % 5, 1, RGB(rc, gc, bc));
      HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

      SelectObject(hdc, brush);
      Rectangle(hdc, 0, 0, 610, 410);
      SelectObject(hdc, pen);
      POINT p;
      MoveToEx(hdc, obj[0].X, obj[0].Y, &p);
      for (int i = 1; i<count; i++)
      {
         LineTo(hdc, obj[i].X, obj[i].Y);
         Sleep(1500 / count);
      }
      LineTo(hdc, obj[0].X, obj[0].Y);
   }

   ~Figura()
   {
      if (obj != NULL) delete[]obj;
   }

};

void main()
{
   system("mode con cols=80 lines=50");
   srand(time(0));
   system("title Фигуры");
   while (1)
   {
      system("cls");
      COORD c = { 0, 0 };
      HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleCursorPosition(h, c);
      Figura f;
      int points;
      cin >> points;
      f.CreateFigura(points, rand() % 255, rand() % 255, rand() % 255);
      f.ShowFigura();
   }
}