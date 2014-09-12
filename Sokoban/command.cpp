#include "command.h"

namespace sokoban {

//static 
bool Command::SetGamePole(GamePole* game_pole) {
  if (game_pole) {
    game_pole_ = game_pole;
  }
  return game_pole;
}

}      // namespace sokoban