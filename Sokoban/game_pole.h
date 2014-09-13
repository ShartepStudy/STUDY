#ifndef GAME_POLE_H
#define GAME_POLE_H

#include <vector>

#include "macros.h"

namespace sokoban {

enum CellType {
  EMPTY   = 0,
  PLAYER  = 1,
  BOX     = 2,
  FREE    = 3,
  WALL    = 4
};

class GamePole {
public:
  GamePole() {}
  ~GamePole() {}

  bool Init(char* file_name);

  int X() const { return x_; }
  int Y() const { return y_; }
  bool SetXY(int x, int y);

  std::vector<CellType> operator[](size_t index) { return pole_[index]; }
    
private:
  std::vector< std::vector<CellType> > pole_;

  int x_;
  int y_;

  DISALLOW_COPY_AND_ASSIGN(GamePole);
};

}   // namespace sokoban

#endif    //  GAME_POLE_H