#include "command_right.h"

#include "game_pole.h"

namespace sokoban {

bool CommandRight::Execute() {
  bool rv = false;
  if (FREE == GetCell(x_ + 1, y_)) {
    SetCell(x_, y_, FREE);
    SetCell(x_ + 1, y_, PLAYER);
    rv = true;
  } else if (BOX == GetCell(x_ + 1, y_) && FREE == GetCell(x_ + 1, y_)) {
    SetCell(x_, y_, FREE);
    SetCell(x_ + 1, y_, PLAYER);
    SetCell(x_ + 2, y_, BOX);
    with_box_ = true;
    rv = true;
  }
  return rv;
}

bool CommandRight::UnExecute() {
  bool rv = false;
  if (with_box_ && FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_ + 1, y_, BOX);
    SetCell(x_ + 2, y_, FREE);
    rv = true;
  } else if (FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_ + 1, y_, FREE);
    rv = true;
  }
  return rv;
}

}         //      namespace sokoban 