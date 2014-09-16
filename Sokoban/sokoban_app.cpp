#include "sokoban_app.h"

#include <conio.h>

#include "command.h"
#include "command_down.h"
#include "command_left.h"
#include "command_right.h"
#include "command_up.h"

namespace sokoban {

SokobanApp::SokobanApp():
    game_pole_(),
    renderer_(game_pole_) //,
//    undo_commands_(),
//    redo_commands_()
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
    if (EXTENDED_BUTTONS == btnCode) {
      btnCode = getch();
    }

    if (UP_BUTTON == btnCode) {
      CommandUp command_up;
      if (command_up.Execute()) {
        //        undo_commands_.Push(command_up);
      }
    } else if (DOWN_BUTTON == btnCode) {
      CommandDown command_down;
      if (command_down.Execute()) {
        //        undo_commands_.Push(command_down);
      }
    } else if (LEFT_BUTTON == btnCode) {
      CommandLeft command_left;
      if (command_left.Execute()) {
        //        undo_commands_.Push(command_left);
      }
    } else if (RIGHT_BUTTON == btnCode) {
      CommandRight command_right;
      if (command_right.Execute()) {
        //        undo_commands_.Push(command_right);
      }
    }
/*    switch (btnCode) {
    case UP_BUTTON:
      CommandUp command_up;
      if (command_up.Execute()) {
//        undo_commands_.Push(command_up);
      }
      break;
    case DOWN_BUTTON:
      CommandDown command_down;
      if (command_down.Execute()) {
//        undo_commands_.Push(command_down);
      }
      break;
    case LEFT_BUTTON:
      CommandLeft command_left;
      if (command_left.Execute()) {
//        undo_commands_.Push(command_left);
      }
      break;
    case RIGHT_BUTTON:
      CommandRight command_right;
      if (command_right.Execute()) {
//        undo_commands_.Push(command_right);
      }
      break;
    }
*/
  } while(true);
}

}   // namespace sokoban
