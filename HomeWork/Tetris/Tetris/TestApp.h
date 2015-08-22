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
   // ������ �� ������ ��������������� ������ (��������� ������ � �������� ����������� ������)
   CFigure mFigure;   
      
   float mDeltaTime;    // ������ ����� ��������� � ���������� �������� ��������� ��������� ������ 
   float mDelay;        // ������ NORMAL_DELAY ���� FAST_DELAY, ���������� �������� ��������� ������
   float mDelayTemp;

   int mNextFigureType; // ������ ����� ���� ������� ������
   int mLineScore;			// ������ ���-�� ��������� �����
   int mDifficalty;			// ������ ������� ���������
private:
   void drawNextFigure();	// �������������� ������ � ���� ������������ ������� ������
   void drawScore();		// ������� �� ����� ���-�� ��������� �����
   void drawLevel();		// ������� �� ����� ������ ���������

   // ����� ��������� ������� ����������� ����� � � ������ ����������� ������� ������� �� �� ������
   void checkFullLines();     
   
   // ����� ������� ������ �n (��������� ������ ����) �� ������, � �������� ��� ���������� ������ 
   // ������ ����
   void delLine(int n);

   // ����� ��������� �� �������� �� ����� ���� (����� ����� ������ ��� �� ����� ���������)
   // ���� ��������, �� ����� ��������� � ���� ���������� � ������
   void checkGameOver();
public:
	TestApp();
   ~TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
};

#endif