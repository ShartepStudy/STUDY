#include "TestApp.h"

void TestApp::drawNextFigure()
{
   for(int i = 1; i < 7; i++)
      for(int j = 1; j < 5; j++)
         SetChar(GAME_POLE_WIDTH + i, j, L'.');

   int dX = (mNextFigureType == 1 ? 3 : 2);
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 2; j++)
         if(FIGURE[mNextFigureType][j][i]) SetChar(GAME_POLE_WIDTH + dX + i, j + 2, L'*');
}

void TestApp::drawScore()
{
   SetChar(GAME_POLE_WIDTH + 9, FIGURE_PREVIEW_POLE_HEIGHT + 4, (char)(mLineScore / 100 + '0'));
   SetChar(GAME_POLE_WIDTH + 10, FIGURE_PREVIEW_POLE_HEIGHT + 4, (char)((mLineScore / 10) % 10 + '0'));
   SetChar(GAME_POLE_WIDTH + 11, FIGURE_PREVIEW_POLE_HEIGHT + 4, (char)(mLineScore % 10 + '0'));
}

void TestApp::drawLevel()
{
   SetChar(GAME_POLE_WIDTH + 10, FIGURE_PREVIEW_POLE_HEIGHT + 8, (char)(mDifficalty / 10 + '0'));
   SetChar(GAME_POLE_WIDTH + 11, FIGURE_PREVIEW_POLE_HEIGHT + 8, (char)(mDifficalty % 10 + '0'));
}

void TestApp::checkFullLines()
{
   for(int y = GAME_POLE_HEIGHT - 2; y > 0; y--)
   {
      bool lineIsFull = true;
      for(int x = 1; x < GAME_POLE_WIDTH; x++)
      {
         if(GetChar(x, y) != '*')
            lineIsFull = false;
      }
      if(lineIsFull) delLine(y++);
   }
}

void TestApp::delLine(int n)
{
   for(int y = n; y > 1; y--)
      for(int x = 1; x < GAME_POLE_WIDTH; x++)
         SetChar(x, y, GetChar(x, y - 1));

   for(int x = 1; x < GAME_POLE_WIDTH; x++)
      SetChar(x, 1, '.');

   mLineScore++;
   drawScore();

   if(mDifficalty < mLineScore/LINES_PER_LEVEL)
   {
	  mDifficalty = mLineScore/LINES_PER_LEVEL;
	  mDelayTemp -= LEVEL_DELAY;
   }
   drawLevel();
}

void TestApp::checkGameOver()
{
   if(mFigure.isGameOver())
   {
      for(int y = GAME_POLE_HEIGHT - 2; y > 0; y--)
         for(int x = 1; x < GAME_POLE_WIDTH; x++)
            SetChar(x, y, '.');
      
	  mLineScore = 0;
	  drawScore();
	  mDifficalty = 0;
	  drawLevel();
	  mDelayTemp = NORMAL_DELAY;
   }
}

TestApp::TestApp(): BaseApp(50, 40), mFigure(*this)
{
   for (int y=0; y < GAME_POLE_HEIGHT; y++)
   {
      for (int x=0; x < FIGURE_PREVIEW_POLE_WIDTH + GAME_POLE_WIDTH; x++) 
      {
         if (y==0 || 
             (y==(GAME_POLE_HEIGHT-1) && x>=0 && x<=GAME_POLE_WIDTH) ||
             x==0 || 
             x==GAME_POLE_WIDTH ||
             (x==(FIGURE_PREVIEW_POLE_WIDTH + GAME_POLE_WIDTH-1) && y>=0 && y<=FIGURE_PREVIEW_POLE_HEIGHT) ||
             (y==FIGURE_PREVIEW_POLE_HEIGHT && x>=GAME_POLE_WIDTH && x<(FIGURE_PREVIEW_POLE_WIDTH + GAME_POLE_WIDTH-1)))
                  SetChar(x, y, L'#');
         else if ((y>0 && y<(GAME_POLE_HEIGHT-1) && x>0 && x<GAME_POLE_WIDTH) ||
                  (y>0 && y<FIGURE_PREVIEW_POLE_HEIGHT && x>GAME_POLE_WIDTH && x<(FIGURE_PREVIEW_POLE_WIDTH + GAME_POLE_WIDTH-1)))
                     SetChar(x, y, L'.');
      }
   };

   mLineScore = 0;
   SetChar(GAME_POLE_WIDTH + 2, FIGURE_PREVIEW_POLE_HEIGHT + 4, L'S');
   SetChar(GAME_POLE_WIDTH + 3, FIGURE_PREVIEW_POLE_HEIGHT + 4, L'c');
   SetChar(GAME_POLE_WIDTH + 4, FIGURE_PREVIEW_POLE_HEIGHT + 4, L'o');
   SetChar(GAME_POLE_WIDTH + 5, FIGURE_PREVIEW_POLE_HEIGHT + 4, L'r');
   SetChar(GAME_POLE_WIDTH + 6, FIGURE_PREVIEW_POLE_HEIGHT + 4, L'e');
   SetChar(GAME_POLE_WIDTH + 7, FIGURE_PREVIEW_POLE_HEIGHT + 4, L':');
   drawScore();

   SetChar(GAME_POLE_WIDTH + 2, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'F');
   SetChar(GAME_POLE_WIDTH + 3, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'i');
   SetChar(GAME_POLE_WIDTH + 4, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'g');
   SetChar(GAME_POLE_WIDTH + 5, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'u');
   SetChar(GAME_POLE_WIDTH + 6, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'r');
   SetChar(GAME_POLE_WIDTH + 7, FIGURE_PREVIEW_POLE_HEIGHT + 6, L'e');
   SetChar(GAME_POLE_WIDTH + 8, FIGURE_PREVIEW_POLE_HEIGHT + 6, L's');
   SetChar(GAME_POLE_WIDTH + 9, FIGURE_PREVIEW_POLE_HEIGHT + 6, L':');

   mDifficalty = 0;
   SetChar(GAME_POLE_WIDTH + 2, FIGURE_PREVIEW_POLE_HEIGHT + 8, L'L');
   SetChar(GAME_POLE_WIDTH + 3, FIGURE_PREVIEW_POLE_HEIGHT + 8, L'e');
   SetChar(GAME_POLE_WIDTH + 4, FIGURE_PREVIEW_POLE_HEIGHT + 8, L'v');
   SetChar(GAME_POLE_WIDTH + 5, FIGURE_PREVIEW_POLE_HEIGHT + 8, L'e');
   SetChar(GAME_POLE_WIDTH + 6, FIGURE_PREVIEW_POLE_HEIGHT + 8, L'l');
   SetChar(GAME_POLE_WIDTH + 7, FIGURE_PREVIEW_POLE_HEIGHT + 8, L':');
   drawLevel();

   mNextFigureType = rand() % 7;

   drawNextFigure();

   mDeltaTime = 0;
   mDelay = NORMAL_DELAY;
   mDelayTemp = 0;
}

TestApp::~TestApp()
{
}

void TestApp::KeyPressed(int btnCode)
{
   if ( btnCode == 224 )
      btnCode = getch();
	switch (btnCode)
   {
   case 80: 
      mDelayTemp = mDelay;
      mDelay = FAST_DELAY;
      break;
   case 75:
      mFigure.moveLeft();
      break;
   case 77:
      mFigure.moveRight();
      break;
   case 32:
      mFigure.rotate();
      break;
   }
}

void TestApp::UpdateF(float deltaTime)
{
   mDeltaTime += deltaTime;
   if(mDeltaTime > mDelay )
   {
      if(!mFigure.moveDown())
      {
         checkGameOver();
         checkFullLines();

         mFigure.newFigure(mNextFigureType);
      
         mNextFigureType = rand() % 7;
         drawNextFigure();
         
         mDelay = mDelayTemp;
      }
      mDeltaTime = 0;
   }
}