#include "renderer.h"

#include <iostream>
#include <vector>

#include "game_pole.h"

namespace sokoban {

void Renderer::Show() {
  for (auto it_y = std::begin(game_pole_()); it_y != std::end(game_pole_()); ++it_y) {
    for (auto it_x = std::begin(*it_y); it_x != std::end(*it_y); ++it_x) {
      std::cout << std::to_string(*it_x);
    }
    std::cout << '\n';
  }
}

}     //    namespace sokoban