#include "renderer.h"

#include <iostream>

namespace sokoban {

Renderer::Renderer():
    kImgStep_(30),
    base_map_(NULL),
    objects_map_(NULL),
    x_(0),
    y_(0),
    width_(0),
    height_(0),
    h_bitmaps_(MAX_CELL_TYPE-1),
    h_child_wnd_(),
    max_width_(30),
    max_height_(30)
{
  for(int i=0; i<MAX_CELL_TYPE-1; ++i) {
    h_bitmaps_[i] = ((HBITMAP)(LoadImageA(NULL, 
                                          (std::to_string(i) + ".bmp").c_str(), 
                                          IMAGE_BITMAP, 
                                          0, 
                                          0, 
                                          LR_LOADFROMFILE | LR_CREATEDIBSECTION)));
  }

  h_child_wnd_.Init(max_width_, max_height_, NULL);

  std::cout << "\n\n\n\t* ";
  HWND hConsole = GetConsoleWindow();
  for (size_t y = 0; y < max_height_; ++y) {
    for (size_t x = 0; x < max_width_; ++x) {
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
    std::cout << "* ";
  }
  h_child_wnd_.SetInitialize(true);

  SetConsoleTitleA("Sokoban");
}

Renderer::~Renderer() {
  std::cout << "\n\n\n\t* ";

  for (size_t y = 0; y < max_height_; ++y) {
    for (size_t x = 0; x < max_width_; ++x) {
      DestroyWindow(h_child_wnd_.GetCell(x, y));
    }
    std::cout << "* ";
  }

  for (auto it : h_bitmaps_) {
    DeleteObject(it);
  }

  std::cout << "\n\n\n\n";
}

void Renderer::Init(GamePole<CellType>* base_map, GamePole<CellType>* objects_map) {
  if (!base_map || !objects_map) {
    throw NullPointerException("Renderer::Init");
  }

  base_map_ = base_map;
  objects_map_ = objects_map;

  width_ = base_map_->GetWidth();
  height_ = base_map_->GetHeight();

  x_ = (max_width_ - width_) / 2;
  y_ = (max_width_ - width_) / 2;
}

void Renderer::Show() {
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      LPARAM h_bitmap;
      CellType obj = objects_map_->GetCell(x, y);
      if (PLAYER == obj) {
        if (BOX_PLACE == base_map_->GetCell(x, y)) {
          h_bitmap = (LPARAM)h_bitmaps_[PLAYER_ON_BOX_PLACE];
        } else {
          h_bitmap = (LPARAM)h_bitmaps_[obj];
        }
      } else if (BOX == obj) {
        h_bitmap = (LPARAM)h_bitmaps_[obj];
      } else {
        h_bitmap = (LPARAM)h_bitmaps_[base_map_->GetCell(x, y)];
      }
      SendMessage(h_child_wnd_.GetCell(x + x_, y + y_),
                  (UINT)STM_SETIMAGE,
                  (WPARAM)IMAGE_BITMAP,
                  h_bitmap);
    }
  }
}

void Renderer::ShowCell(size_t x, size_t y, CellType cell_type) {
  SendMessage(h_child_wnd_.GetCell(x + x_, y + y_),
              (UINT)STM_SETIMAGE,
              (WPARAM)IMAGE_BITMAP,
              (LPARAM)h_bitmaps_[cell_type]);
}

void Renderer::ClearScreen() {
  for (size_t y = 1; y < max_height_-1; y++) {
    for (size_t x = 1; x < max_width_-1; x++) {
      SendMessage(h_child_wnd_.GetCell(x, y),
                  (UINT)STM_SETIMAGE,
                  (WPARAM)IMAGE_BITMAP,
                  (LPARAM)h_bitmaps_[BLACK]);
    }
  }
}

} //  namespace sokoban
