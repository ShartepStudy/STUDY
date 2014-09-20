#include "renderer.h"

#include <iostream>
#include <vector>

#include "game_pole.h"

namespace sokoban {

void Renderer::Show() {
  if (game_pole_.IsModify()) {
    system("cls");
    for (auto it_y: game_pole_()) {
      for (auto it_x: it_y) {
        std::cout << std::to_string(it_x);
      }
      std::cout << '\n';
    }
    
    game_pole_.SetUnModify();
  }
}

}     //    namespace sokoban