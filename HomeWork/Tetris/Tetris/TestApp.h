#ifndef _TEST_APP_H_
#define _TEST_APP_H_

//class TestApp;

#include "Figure.h"
#include "BaseApp.h"
#include "const.h"

#include <conio.h>

class TestApp : public BaseApp
{
private:
   // ссылка на объект инкапсулирующий фигуру (обработка сдвига и поворота отображения фигуры)
   CFigure mFigure;   
      
   float mDeltaTime;    // хранит время прошедшее с пердыдущей итерации обработки опускания фигуры 
   float mDelay;        // хранит NORMAL_DELAY либо FAST_DELAY, определяет скорость опускания фигуры
   float mDelayTemp;

   int mNextFigureType; // хранит номер типа будущей фигуры
   int mLineScore;			// хранит кол-во собранных линий
   int mDifficalty;			// хранит уровень сложности
private:
   void drawNextFigure();	// перерисовывает фигуру в поле отображающем БУДУЩУЮ ФИГУРУ
   void drawScore();		// выводит на экран кол-во собранных линий
   void drawLevel();		// выводит на экран уовень сложности

   // метод проверяет наличие заполненных линий и в случае обнаружения таковых удалает их из буфера
   void checkFullLines();     
   
   // метод удаляет строку №n (нумерация сверху вниз) из буфера, и сдвигает все пердыдущие строки 
   // сверху вниз
   void delLine(int n);

   // метод проверяет не наступил ли конец игры (когда новая фигура уже не может появиться)
   // если наступил, то буфер очищается и игра начинается с начала
   void checkGameOver();
public:
	TestApp();
   ~TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
};

#endif