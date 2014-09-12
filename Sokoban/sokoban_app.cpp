#include "sokoban_app.h"

#include <conio.h>

namespace sokoban {

SokobanApp::SokobanApp():
    game_pole_(),
    renderer_(game_pole_),
    undo_commands_(),
    redo_commands_()
{
  Command::SetGamePole(&game_pole_);
}

void SokobanApp::Run() {
  game_pole_.Init("level_1.dat"); 

  do {
    if (game_pole_.IsModify()) {
      renderer_.Show();
    }

    int btnCode = getch();
    if (btnCode == 224) {
      btnCode = getch();
    }

    switch (btnCode) {
    case 72:
      CommandUp command_up;
      if (command_up.Execute()) {
        undo_commands_.Push(command_up);
      }
      break;
    case 80:
      CommandDown command_down;
      if (command_down.Execute()) {
        undo_commands_.Push(command_down);
      }
      break;
    case 75:
      CommandLeft command_left;
      if (command_left.Execute()) {
        undo_commands_.Push(command_left);
      }
      break;
    case 77:
      CommandRight command_right;
      if (command_right.Execute()) {
        undo_commands_.Push(command_right);
      }
      break;
    default:
    }

  } while(true);
}

}   // namespace sokoban
