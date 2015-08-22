#ifndef _FIGURE_H_
#define _FIGURE_H_

class TestApp;

//#include "TestApp.h"
#include "const.h"

#include <time.h>
#include <Windows.h>

class CFigure
{
private:
   // ссылка на объект осуществл€ющий вывод на экран, необходима дл€ доступа к буферу экрана
   // с помощью методов GetChar(), SetChar()
   TestApp & mParent;   
   
   //текущие кордината верхнего левого угла вигуры
   int x;   
   int y;
   
   int mType;  // номер типа фигуры, характеризует ее форму

   int mFigureScore; // кол-во пройденных фигур
private:
   void clearFigure();  // метод затирает текущую фигуру в буфере экрана
   void drawFigure();   // метод отрисовывает текущую фигуру в буфере экрана
   void drawScore();	// выводит на экран кол-во сыгранных фигур

   // методы провер€ет возможно ли сдвинуть(повернуть) фигуру в соответствующем направлении
   bool canMoveDown();  
   bool canMoveLeft();
   bool canMoveRight();
   bool canRotate();

   // методы возвращаютт высоту и ширину фигуры в соответствующем столбце columnIndex
   // и строке strIndex, необходимы дл€ работы методов canMoveDown() и canMoveRight()
   int figureHeight(int columnIndex);  
   int figureWidth(int strIndex);      
   
   // метод возвращает номер типа фигуры который она должна приобрести после поворота
   int rotateType(int type);
public:
   CFigure(TestApp & parent);
   ~CFigure();

   // методы сдвигаю(поворачивают) фигуру в соответствующем направлении
   bool moveDown();
   void moveLeft();
   void moveRight();
   void rotate();

   void newFigure(int type); // обновл€ет параметры фигуры перед по€влением на экране новой фигуры
   bool isGameOver();   // провер€ет не закончена ли игра, в св€зи с тем что новым фигурам негде по€вл€тьс€
};

#endif

