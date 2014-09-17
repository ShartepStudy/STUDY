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
    renderer_(game_pole_),
    undo_commands_(),
    redo_commands_()
{
  Command::SetGamePole(&game_pole_);
}

void SokobanApp::Run() {
  game_pole_.Init("level_2.dat"); 

  do {
    renderer_.Show();

    std::shared_ptr<Command> command;
    
    int btnCode = getch();
    if (EXTENDED_BUTTONS == btnCode) {
      btnCode = getch();
    }

    switch (btnCode) {
    case UP_BUTTON: 
      command.reset(new CommandUp);
      UndoHelper(command);
      break;
    case DOWN_BUTTON: 
      command.reset(new CommandDown);
      UndoHelper(command);
      break;
    case LEFT_BUTTON: 
      command.reset(new CommandLeft);
      UndoHelper(command);
      break;
    case RIGHT_BUTTON: 
      command.reset(new CommandRight);
      UndoHelper(command);
      break;
    case U_BUTTON:
    case u_BUTTON:
      if (!undo_commands_.empty()) {
        command = undo_commands_.top();
        undo_commands_.pop();
        command->UnExecute();
        redo_commands_.push(command);
      }
      break;
    case R_BUTTON:
    case r_BUTTON:
      if (!redo_commands_.empty()) {
        command = redo_commands_.top();
        redo_commands_.pop();
        command->Execute();
        undo_commands_.push(command);
      }
      break;
    }

  } while(true);
}

void SokobanApp::UndoHelper(std::shared_ptr<Command>& command) {
  if (command->Execute()) {
    undo_commands_.push(command);
    if (!redo_commands_.empty()) {
      redo_commands_ = std::stack<std::shared_ptr<Command> >();
    }
  }
}

}   // namespace sokoban
