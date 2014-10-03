#include "renderer.h"

#include "game_pole.h"

namespace sokoban {

Renderer::Renderer(GamePole<CellType>& base_map, GamePole<CellType>& objects_map):
    kImgStep_(30),
    base_map_(base_map),
    objects_map_(objects_map),
    h_bitmaps_(MAX_CELL_TYPE),
    h_child_wnd_()
{
  for(int i=0; i<MAX_CELL_TYPE; ++i) {
    h_bitmaps_[i] = ((HBITMAP)(LoadImageA(NULL, 
                                          (std::to_string(i) + ".bmp").c_str(), 
                                          IMAGE_BITMAP, 
                                          0, 
                                          0, 
                                          LR_LOADFROMFILE | LR_CREATEDIBSECTION)));
  }
}

Renderer::~Renderer() {
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      DestroyWindow(h_child_wnd_.GetCell(x, y));
    }
  }

  for (auto it : h_bitmaps_) {
    DeleteObject(it);
  }
}

void Renderer::Init() {
  width_ = base_map_.GetWidth();
  height_ = base_map_.GetHeight();

  h_child_wnd_.Init(width_, height_, NULL);
  
  HWND hConsole = GetConsoleWindow();
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      h_child_wnd_.SetCell(x, y, 
                           CreateWindowEx(0,
                                          L"static",
                                          NULL,
                                          WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP,
                                          x*kImgStep_,
                                          y*kImgStep_,
                                          0,
                                          0,
                                          hConsole,
                                          (HMENU)((y + 1)*(x + 1)),
                                          GetModuleHandle(0),
                                          NULL));
    }
  }
  h_child_wnd_.SetInitialize(true);
}

void Renderer::Show() {
  //  SetConsoleTitleA("JAPAN");

  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      LPARAM h_bitmap;
      CellType obj = objects_map_.GetCell(x, y);
      if (PLAYER == obj) {
        if (BOX_PLACE == base_map_.GetCell(x, y)) {
          h_bitmap = (LPARAM)h_bitmaps_[PLAYER_ON_BOX_PLACE];
        } else {
          h_bitmap = (LPARAM)h_bitmaps_[obj];
        }
      } else if (BOX == obj) {
        h_bitmap = (LPARAM)h_bitmaps_[obj];
      } else {
        h_bitmap = (LPARAM)h_bitmaps_[base_map_.GetCell(x, y)];
      }
      SendMessage(h_child_wnd_.GetCell(x, y),
                  (UINT)STM_SETIMAGE,
                  (WPARAM)IMAGE_BITMAP,
                  h_bitmap);
    }
  }
}

void Renderer::ShowCell(size_t x, size_t y, CellType cell_type) {
  SendMessage(h_child_wnd_.GetCell(x, y),
              (UINT)STM_SETIMAGE,
              (WPARAM)IMAGE_BITMAP,
              (LPARAM)h_bitmaps_[cell_type]);
}

void Renderer::SetCursor(size_t x, size_t y) {
  COORD position;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  position.X = x;
  position.Y = y;

  SetConsoleCursorPosition(hConsole, position);
}

} //  namespace sokoban
