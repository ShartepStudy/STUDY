#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <windows.h>

#include "game_pole.h"
#include "macros.h"

namespace sokoban {
//  typedef std::pair<CellType, HWND> CellPair;
  
class Renderer {
public:
  Renderer(GamePole<CellType>& base_map, GamePole<CellType>& objects_map);
  ~Renderer() {};

  void Init();
  void Show();

private:
  const size_t kImgStep_;

  GamePole<CellType>& base_map_;
  GamePole<CellType>& objects_map_;

  std::vector<HBITMAP> h_bitmaps_;
  GamePole<HWND> h_child_wnd_;

  size_t width_;
  size_t height_;

  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

}           //    namespace sokoban

#endif      //    RENDERER_H