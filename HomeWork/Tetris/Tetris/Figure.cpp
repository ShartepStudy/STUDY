#include "Figure.h"
#include "TestApp.h"

void CFigure::clearFigure()
{
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
         if(FIGURE[mType][j][i]) mParent.SetChar(x + i, y + j, L'.');
}

void CFigure::drawFigure()
{
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
         if(FIGURE[mType][j][i]) mParent.SetChar(x + i, y + j, L'*');
}

void CFigure::drawScore()
{
   mParent.SetChar(GAME_POLE_WIDTH + 11, FIGURE_PREVIEW_POLE_HEIGHT + 6, (char)(mFigureScore / 1000 + '0'));
   mParent.SetChar(GAME_POLE_WIDTH + 12, FIGURE_PREVIEW_POLE_HEIGHT + 6, (char)((mFigureScore / 100) % 100 + '0'));
   mParent.SetChar(GAME_POLE_WIDTH + 13, FIGURE_PREVIEW_POLE_HEIGHT + 6, (char)((mFigureScore / 10) % 10 + '0'));
   mParent.SetChar(GAME_POLE_WIDTH + 14, FIGURE_PREVIEW_POLE_HEIGHT + 6, (char)(mFigureScore % 10 + '0'));
}

bool CFigure::canMoveDown()
{   
   for(int i = 0; i < 4; i++)
   {
      int fH = figureHeight(i);
	  if(fH != -1 && mParent.GetChar(x + i, y + fH + 1) != '.') {
		  mFigureScore++;
		  drawScore();
		  return false;
	  }
   }

   return true;
}

bool CFigure::canMoveLeft()
{
   for(int i = 0; i < 4; i++)
      if( FIGURE[mType][i][0] && mParent.GetChar(x - 1, y + i) != '.' ) 
         return false;

   return true;
}

bool CFigure::canMoveRight()
{
   for(int i = 0; i < 4; i++)
   {
      int fW = figureWidth(i);
      if(fW!=-1 && mParent.GetChar(x + fW + 1, y + i) != '.')  
         return false;
   }

   return true;
}

bool CFigure::canRotate()
{
   int type = rotateType(mType);
   clearFigure();
   for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
         if(FIGURE[type][i][j] && mParent.GetChar(x + j, y + i) != '.')
         {
            drawFigure();
            return false;
         }

   return true;
}

int CFigure::figureHeight(int columnIndex)
{
   for(int j = 3; j >= 0; j--)
      if(FIGURE[mType][j][columnIndex]) return j;
   
   return -1;
}

int CFigure::figureWidth(int strIndex)
{
   for(int j = 3; j >= 0; j--)
      if(FIGURE[mType][strIndex][j]) return j;

   return -1;
}

int CFigure::rotateType(int type)
{
   switch(type)
   {
   case 0: return 7;
   case 2: return 8;
   case 3: return 9;
   case 4: return 10;
   case 5: return 13;
   case 6: return 16;
   case 7: return 0;
   case 8: return 2;
   case 9: return 3;
   case 10:
   case 11:
   case 13:
   case 14:
   case 16:
   case 17: return ++type;
   case 12: return 4;
   case 15: return 5;
   case 18: return 6;
   }
}

CFigure::CFigure(TestApp & parent): mParent(parent)
{
   srand((int) time(NULL));
   mType = rand() % 7;

   x = GAME_POLE_WIDTH / 2;
   y = 1;

   mFigureScore = 0;
   drawScore();
}


CFigure::~CFigure()
{}

bool CFigure::moveDown()
{
   if(canMoveDown())
   {
      clearFigure();
      y++;
      drawFigure();
      return true;
   }
   return false;
}

void CFigure::moveLeft()
{
   if(canMoveLeft())
   {
      clearFigure();
      x--;
      drawFigure();
   }
}

void CFigure::moveRight()
{
   if(canMoveRight())
   {
      clearFigure();
      x++;
      drawFigure();
   }
}

void CFigure::rotate()
{
   if(canRotate())
   {
      mType = rotateType(mType);
      drawFigure();
   }
}

void CFigure::newFigure(int type)
{
   y = 1;
   x = GAME_POLE_WIDTH / 2;
   mType = type;
}

bool CFigure::isGameOver()
{
   if(y < 2) 
   {
	   mFigureScore = 0;
	   drawScore();
	   return true;
   }
   return false;
}