#include "renderer.h"

//#include <iostream>
//#include <vector>

#include "game_pole.h"

namespace sokoban {
//
//namespace {
//
//HWND BCX_Bitmap(const char* Text, HWND hWnd, int id, int X, int Y, int W, int H, int Res, int Style, int Exstyle) {
//  HWND A;
//  HBITMAP hBitmap;
//
//  // set default style
//  if (!Style) Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;
//
//  // form for the image
//  A = CreateWindowEx(Exstyle, L"static", NULL, Style, X, Y, 0, 0, hWnd, (HMENU)id, GetModuleHandle(0), NULL);
//
//  // Text contains filename
////  hBitmap = (HBITMAP)LoadImageA(0, Text, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//
//  // auto-adjust width and height
////  if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, W, H, LR_COPYRETURNORG);
//  SendMessage(A, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
////  if (W || H) SetWindowPos(A, HWND_TOP, X, Y, W, H, SWP_DRAWFRAME);
//  return A;
//}
//
//}       // namespace

Renderer::Renderer(GamePole& game_pole): 
    game_pole_(game_pole)
//    h_bitmaps_(MAX_CELL_TYPE)
//    h_child_wnd_() 
{
  for(int i=0; i<MAX_CELL_TYPE; ++i) {
    h_bitmaps_.push_back((HBITMAP)LoadImageA(NULL, 
                                             (std::to_string(i) + ".bmp").c_str(), 
                                             IMAGE_BITMAP, 
                                             0, 
                                             0, 
                                             LR_LOADFROMFILE | LR_CREATEDIBSECTION));
  }

  //const int img_step = 50;
  //std::vector<HWND> vector_x;
  //HWND hWnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
  //int Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;
  //for (size_t y = 0; y < game_pole_.GetHeight(); ++y) {
  //  for (size_t x = 0; x < game_pole_.GetWidth(); ++x) {
  //    vector_x.push_back(CreateWindowEx(0, 
  //                                      L"static", 
  //                                      NULL, 
  //                                      Style,
  //                                      x*img_step,
  //                                      y*img_step,
  //                                      0, 
  //                                      0, 
  //                                      hWnd, 
  //                                      (HMENU)((y+1)*(x+1)), 
  //                                      GetModuleHandle(0), 
  //                                      NULL));
  //  }
  //  h_child_wnd_.push_back(vector_x);
    //vector_x.clear();
  //}
}


void Renderer::Show() {
  //  SetConsoleTitleA("JAPAN");

  if (game_pole_.IsModify()) {
//    system("cls");
    //int id = 0, x = 0, y = 0;
    //const int img_step = 50;

    int x=0, y=0;
    for (auto it_y : game_pole_()) {
      for (auto it_x: it_y) {
        SendMessage(it_x.second, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)h_bitmaps_[it_x.first]);
//        BCX_Bitmap(file_name.c_str(), hwnd, ++id, x, y, img_step, img_step, 0, 0, 0);
//        x += img_step;
//        ++x;
      }
      //x = 0;
      //y += img_step;
//      ++y;
    }
    game_pole_.SetUnModify();
  }
}

}     //    namespace sokoban
