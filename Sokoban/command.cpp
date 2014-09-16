#include "command.h"

#include "game_pole.h"

namespace sokoban {

Command::Command(): with_box_(false) {
  if (game_pole_) {
    x_ = game_pole_->X();
    y_ = game_pole_->X();
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