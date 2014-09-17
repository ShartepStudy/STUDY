#include "command.h"

namespace sokoban {

GamePole* Command::game_pole_ = NULL;

Command::Command(): with_box_(false) {
  if (game_pole_) {
    x_ = game_pole_->X();
    y_ = game_pole_->Y();
  }
}

//static 
bool Command::SetGamePole(GamePole* game_pole) {
  if (game_pole) {
    game_pole_ = game_pole;
  }
  return game_pole;
}

bool Command::ExecuteHelper(int dx, int dy) {   //dx=0 dy=1
  bool rv = true;
  if (FREE == GetCell(x_ + dx, y_ + dy)) {
    SetCell(x_, y_, FREE);
    SetCell(x_ + dx, y_ + dy, PLAYER);
  } else if (BOX == GetCell(x_ + dx, y_ + dy) && FREE == GetCell(x_ + 2*dx, y_ + 2*dy)) {
    SetCell(x_, y_, FREE);
    SetCell(x_ + dx, y_ + dy, PLAYER);
    SetCell(x_ + 2*dx, y_ + 2*dy, BOX);
    with_box_ = true;
  } else {
    rv = false;
  }
  return rv;
}

bool Command::UnExecuteHelper(int dx, int dy) {
  bool rv = true;
  if (FREE == GetCell(x_, y_)) {
    SetCell(x_, y_, PLAYER);
    if (with_box_) {
      SetCell(x_ + dx, y_ + dy, BOX);
      SetCell(x_ + 2*dx, y_ + 2*dy, FREE);
    } else {
      SetCell(x_ + dx, y_ + dy, FREE);
    }
  } else {
    rv = false;
  }
  return rv;
}

void Command::SetCell(size_t x, size_t y, CellType data) { 
  (*game_pole_)[y][x] = data; 
  if (PLAYER == data) {
    game_pole_->SetXY(x, y);
  }
  game_pole_->SetModify();
}

}      // namespace sokoban