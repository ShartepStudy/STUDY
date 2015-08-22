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
   // ������ �� ������ �������������� ����� �� �����, ���������� ��� ������� � ������ ������
   // � ������� ������� GetChar(), SetChar()
   TestApp & mParent;   
   
   //������� ��������� �������� ������ ���� ������
   int x;   
   int y;
   
   int mType;  // ����� ���� ������, ������������� �� �����

   int mFigureScore; // ���-�� ���������� �����
private:
   void clearFigure();  // ����� �������� ������� ������ � ������ ������
   void drawFigure();   // ����� ������������ ������� ������ � ������ ������
   void drawScore();	// ������� �� ����� ���-�� ��������� �����

   // ������ ��������� �������� �� ��������(���������) ������ � ��������������� �����������
   bool canMoveDown();  
   bool canMoveLeft();
   bool canMoveRight();
   bool canRotate();

   // ������ ����������� ������ � ������ ������ � ��������������� ������� columnIndex
   // � ������ strIndex, ���������� ��� ������ ������� canMoveDown() � canMoveRight()
   int figureHeight(int columnIndex);  
   int figureWidth(int strIndex);      
   
   // ����� ���������� ����� ���� ������ ������� ��� ������ ���������� ����� ��������
   int rotateType(int type);
public:
   CFigure(TestApp & parent);
   ~CFigure();

   // ������ �������(������������) ������ � ��������������� �����������
   bool moveDown();
   void moveLeft();
   void moveRight();
   void rotate();

   void newFigure(int type); // ��������� ��������� ������ ����� ���������� �� ������ ����� ������
   bool isGameOver();   // ��������� �� ��������� �� ����, � ����� � ��� ��� ����� ������� ����� ����������
};

#endif

