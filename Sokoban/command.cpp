#include "command.h"

namespace sokoban {

class CommandHelperFree: CommandHelper {
  virtual bool ExecuteHelper(GamePole* game_pole, int dx, int dy) {
    int x = game_pole->X();
    int y = game_pole->Y();
    game_pole->SetCell(x + dx, y + dy, PLAYER);
  }

  virtual bool UnExecuteHelper(GamePole* game_pole, int x, int y) {
    int x = game_pole->X();
    int y = game_pole->Y();


    if (FREE == game_pole->GetCell(x, y)) {
      game_pole->SetCell(x, y, PLAYER);
    } else if (BOX_PLACE == game_pole->GetCell(x, y)) {
      game_pole->SetCell(x, y, PLAYER_ON_BOX_PLACE);
    }
  }
};

GamePole* Command::game_pole_ = NULL;

Command::Command(int dx, int dy): dx_(dx), dy_(dy) {
  if (game_pole_) {
    x_ = game_pole_->X();
    y_ = game_pole_->Y();
  }

  switch (game_pole_->GetCell(x_ + dx_, y_ + dy_)) {
  case FREE: command_helper_.reset(new CommandHelperFree()); break;
  case BOX_PLACE: command_helper_.reset(new CommandHelperBoxPlace()); break;
  case BOX:
    CellType ct = game_pole_->GetCell(x_ + 2 * dx_, y_ + 2 * dy_);
    if (FREE == ct) {
      command_helper_.reset(new CommandHelperFreeAfterBox());
    } else if (BOX_PLACE == ct) {
      command_helper_.reset(new CommandHelperBoxPlaceAfterBox());
    }
    break;
  }
}

//static 
bool Command::SetGamePole(GamePole* game_pole) {
  if (game_pole) {
    game_pole_ = game_pole;
  }
  return game_pole;
}

}      // namespace sokoban