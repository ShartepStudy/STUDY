#include "command_up.h"

#include "game_pole.h"

namespace sokoban {

bool CommandUp::Execute() {
  bool rv = false;
  if (FREE == GetCell(x_, y_ - 1)) {
    SetCell(x_, y_, FREE);
    SetCell(x_, y_ - 1, PLAYER);
    game_pole_->SetXY(x_, y_ - 1);
    rv = true;
  } else if (BOX == GetCell(x_, y_ - 1) && FREE == GetCell(x_, y_ - 2)) {
    SetCell(x_, y_, FREE);
    SetCell(x_, y_ - 1, PLAYER);
    SetCell(x_, y_ - 2, BOX);
    game_pole_->SetXY(x_, y_ - 1);
    with_box_ = true;
    rv = true;
  }
  return rv;
}

bool CommandUp::UnExecute() {
  bool rv = false;
  if (with_box_ && FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_, y_ - 1, BOX);
    SetCell(x_, y_ - 2, FREE);
    game_pole_->SetXY(x_, y_);
    rv = true;
  } else if (FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    SetCell(x_, y_ - 1, FREE);
    game_pole_->SetXY(x_, y_ );
    rv = true;
  }
  return rv;
}

}         //      namespace sokoban 