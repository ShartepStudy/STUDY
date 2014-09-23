#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <windows.h>

#include "macros.h"

namespace sokoban {

class GamePole;
  
class Renderer {
public:
  Renderer(GamePole& game_pole);
  ~Renderer() {};

  void Show();

private:
  GamePole& game_pole_;

  std::vector<HBITMAP> h_bitmaps_;
  std::vector<std::vector<HWND> > h_child_wnd_;

  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

}           //    namespace sokoban

#endif      //    RENDERER_H