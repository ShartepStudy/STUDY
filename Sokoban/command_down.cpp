#include "command_down.h"

#include "game_pole.h"

namespace sokoban {

bool CommandDown::Execute() {
  bool rv = false;
  if (FREE == GetCell(x_, y_ + 1)) {
    SetCell(x_, y_, FREE);
    SetCell(x_, y_ + 1, PLAYER);
    rv = true;
  } else if (BOX == GetCell(x_, y_ + 1) && FREE == GetCell(x_, y_ + 2)) {
    SetCell(x_, y_, FREE);
    SetCell(x_, y_ + 1, PLAYER);
    SetCell(x_, y_ + 2, BOX);
    with_box_ = true;
    rv = true;
  }
  return rv;
}

bool CommandDown::UnExecute() {
  bool rv = false;
  if (with_box_ && FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_, y_ + 1, BOX);
    SetCell(x_, y_ + 2, FREE);
    rv = true;
  } else if (FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_, y_ + 1, FREE);
    rv = true;
  }
  return rv;
}

}         //      namespace sokoban 