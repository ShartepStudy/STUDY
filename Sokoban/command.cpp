#include "command.h"
#include "sokoban_exception.h"

namespace sokoban {

GamePole<CellType>* Command::base_map_ = NULL;
GamePole<CellType>* Command::objects_map_ = NULL;

Command::Command(): 
    x_(0),
    y_(0),
    with_box_(false)
{
  if (objects_map_) {
    x_ = objects_map_->X();
    y_ = objects_map_->Y();
  }
}

bool Command::ExecuteHelper(int dx, int dy) {
  bool result = false;
  if (BOX == objects_map_->GetCell(x_ + dx, y_ + dy)) {
    CellType ct = base_map_->GetCell(x_ + 2 * dx, y_ + 2 * dy);
    if (EMPTY == objects_map_->GetCell(x_ + 2*dx, y_ + 2*dy) && 
        (FREE == ct || BOX_PLACE == ct)) {
      with_box_ = true;
      objects_map_->SetCell(x_ + 2 * dx, y_ + 2 * dy, BOX);
      result = true;
    } 
  } else {
    CellType ct = base_map_->GetCell(x_ + dx, y_ + dy);
    result = (FREE == ct || BOX_PLACE == ct); 
  }

  if (result) {
    objects_map_->SetCell(x_ + dx, y_ + dy, PLAYER);
    objects_map_->SetCell(x_, y_, EMPTY);
    objects_map_->SetXY(x_ + dx, y_ + dy);
  }

  return result;
}

bool Command::UnExecuteHelper(int dx, int dy) {
  bool result = false;
  if (with_box_) {
    objects_map_->SetCell(x_ + dx, y_ + dy, BOX);
    objects_map_->SetCell(x_ + 2 * dx, y_ + 2 * dy, EMPTY);
    result = true;
  } else {
    objects_map_->SetCell(x_ + dx, y_ + dy, EMPTY);
    result = true;
  }

  if (result) {
    objects_map_->SetCell(x_, y_, PLAYER);
    objects_map_->SetXY(x_, y_);
  }

  return result;
}

//static 
void Command::SetGamePole(GamePole<CellType>* base_map, GamePole<CellType>* objects_map) {
  if (base_map && objects_map) {
    base_map_ = base_map;
    objects_map_ = objects_map;
  } else {
    throw NullPointerException("Command::SetGamePole");
  }
}

}      // namespace sokoban