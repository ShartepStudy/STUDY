
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

#pragma comment(lib,"msimg32.lib")

HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
HDC hdc = GetDC(hwnd); // данные типа HDC представляют собой 32-разрядное целое беззнаковое число.
// после получения дескриптора контекста программа может использовать функции графического интерфейса.

void _rect(int left, int top, int width, int height) {
  Rectangle(hdc, left, top, left + width, top + height);
}

void _ellips(int left, int top, int width, int height) {
  Ellipse(hdc, left, top, left + width, top + height);
}

HWND BCX_Bitmap(char* Text, HWND hWnd, int id, int X, int Y, int W, int H, int Res, int Style, int Exstyle) {
  HWND A;
  HBITMAP hBitmap;

  // set default style
  if (!Style) Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

  // form for the image
  A = CreateWindowEx(Exstyle, L"static", NULL, Style, X, Y, 0, 0, hWnd, (HMENU)id, GetModuleHandle(0), NULL);

  // Text contains filename
  hBitmap = (HBITMAP)LoadImageA(0, Text, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

  // auto-adjust width and height
  if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, W, H, LR_COPYRETURNORG);
  SendMessage(A, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
  if (W || H) SetWindowPos(A, HWND_TOP, X, Y, W, H, SWP_DRAWFRAME);
  return A;
}

void main() {
  SetConsoleTitleA("JAPAN");

  HPEN white_pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
  HBRUSH white_brush = CreateSolidBrush(RGB(255, 255, 255));

  SelectObject(hdc, white_pen);
  SelectObject(hdc, white_brush);

  //_rect(0,0,200,120);

  DeleteObject(white_pen);
  DeleteObject(white_brush);

  //////////////////////////////////

  HPEN red_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
  HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));

  SelectObject(hdc, red_pen);
  SelectObject(hdc, red_brush);

  //_ellips(20+40,20,80,80);

  //RoundRect(hdc,200,200,400,400,20,20);

  //Pie(hdc,200,200,300,300,0,0,0,0);
  //Pie(hdc,200,200,300,300,200,200,300,300);
  //Pie(hdc,200,200,300,300,250,250,300,300);
  //Pie(hdc,200,200,300,300,300,200,300,300);

  //Chord(hdc,200,200,300,300,300,220,200,280);

  //Arc(hdc,0,0,200,500,0,15,200,185);

  /*POINT p;
  MoveToEx(hdc,0,0,&p);
  //LineTo(hdc,0,0);
  LineTo(hdc,200,0);
  LineTo(hdc,200,200);
  LineTo(hdc,0,200);
  LineTo(hdc,0,0);

  MoveToEx(hdc,200,200,&p);
  LineTo(hdc,400,400); */

  DeleteObject(red_pen);
  DeleteObject(red_brush);

  /* LOGFONT font;
  font.lfHeight =  65;// Устанавливает высоту шрифта или символа
  font.lfWidth =  0;// Устанавливает среднюю ширину символов в шрифте
  font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
  font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
  font.lfWeight = 100;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
  font.lfItalic = 0;// Устанавливает курсивный шрифт
  font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
  font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
  font.lfCharSet = RUSSIAN_CHARSET;// Устанавливает набор символов
  font.lfOutPrecision = 0;// Устанавливает точность вывода
  font.lfClipPrecision = 0;// Устанавливает точность отсечения
  font.lfQuality = 0;// Устанавливает качество вывода
  font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта
  lstrcpy(font.lfFaceName , L"Calibri");//  устанавливает название шрифта

  HFONT hfont;
  hfont = CreateFontIndirect(&font);

  SetTextColor(hdc,RGB(255,0,0));

  SelectObject(hdc,hfont);
  TextOutA(hdc,50,50,"LOLOLO",6); */

  /*
  POINT p;
  MoveToEx(hdc,10,10,&p);
  LineTo(hdc,200,50);
  LineTo(hdc,200,200);
  LineTo(hdc,10,200);
  LineTo(hdc,10,10);

  FloodFill(hdc,100,100,RGB(255,0,0)); */

  /*

  TRIVERTEX        vert[2];
  GRADIENT_RECT    gRect;

  vert [0] .x      = 0;
  vert [0] .y      = 0;
  vert [0] .Red    = 0xFF00;
  vert [0] .Green  = 0x0000;
  vert [0] .Blue   = 0x0000;

  vert [1] .x      = 200;
  vert [1] .y      = 200;
  vert [1] .Red    = 0x0000;
  vert [1] .Green  = 0x0000;
  vert [1] .Blue   = 0xFF00;

  gRect.UpperLeft  = 0;
  gRect.LowerRight = 1;

  GradientFill(hdc,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);

  */

  BCX_Bitmap("C:\\1.bmp", hwnd, 1, 10, 10, 0, 0, 0, 0, 0);

  ReleaseDC(hwnd, hdc);

  ////////////////////////////////////////////////////////////////////

  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.bVisible = 0;
  cci.dwSize = 100;
  SetConsoleCursorInfo(h, &cci);
  Sleep(INFINITE);
}