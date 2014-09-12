#include "game_pole.h"

#include <fstream>

namespace sokoban {

bool GamePole::Init(char* file_name) {
  std::fstream file(file_name);


}

bool GamePole::SetXY(int x, int y) {
  bool rv = (PLAYER == pole_[x][y]);
  
  if (rv) {
    x_ = x;
    y_ = y;
  }
  
  return rv;
}

}   // namespace sokoban