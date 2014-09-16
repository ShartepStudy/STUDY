#ifndef SOKOBAN_APP_H
#define SOKOBAN_APP_H

#include "macros.h"

#include "game_pole.h"
#include "renderer.h"
//#include "command_stack.h"

namespace sokoban {

enum ButtonCode {
  UP_BUTTON = 72,
  LEFT_BUTTON = 75,
  RIGHT_BUTTON = 77,
  DOWN_BUTTON = 80,
  EXTENDED_BUTTONS = 224
};

class SokobanApp {
public:
  SokobanApp();
  ~SokobanApp() {};
  
  void Run();

private:
  GamePole game_pole_;
  Renderer renderer_;
//  CommandStack undo_commands_;
//  CommandStack redo_commands_;

  DISALLOW_COPY_AND_ASSIGN(SokobanApp);
};

}   // namespace sokoban

#endif    //  SOKOBAN_APP_H