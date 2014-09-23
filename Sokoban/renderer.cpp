#include "renderer.h"

#include "game_pole.h"

namespace sokoban {

Renderer::Renderer(GamePole& game_pole): game_pole_(game_pole) {
  for(int i=0; i<MAX_CELL_TYPE; ++i) {
    h_bitmaps_.push_back((HBITMAP)LoadImageA(NULL, 
                                             (std::to_string(i) + ".bmp").c_str(), 
                                             IMAGE_BITMAP, 
                                             0, 
                                             0, 
                                             LR_LOADFROMFILE | LR_CREATEDIBSECTION));
  }
}


void Renderer::Show() {
  //  SetConsoleTitleA("JAPAN");

  if (game_pole_.IsModify()) {

    int x=0, y=0;
    for (auto it_y : game_pole_()) {
      for (auto it_x: it_y) {
        SendMessage(it_x.second, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)h_bitmaps_[it_x.first]);
      }
    }
    game_pole_.SetUnModify();
  }
}

}     //    namespace sokoban
