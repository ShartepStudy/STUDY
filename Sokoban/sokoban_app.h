#ifndef SOKOBAN_APP_H
#define SOKOBAN_APP_H

#include "macros.h"

#include "game_pole.h"
#include "renderer.h"
#include "command.h"
#include "stack.h"

namespace sokoban {

class SokobanApp {
public:
  SokobanApp();
  ~SokobanApp() {};
  
  void Run();

private:
  GamePole game_pole_;
  Renderer renderer_;
  Stack<Command> undo_commands_;
  Stack<Command> redo_commands_;

  DISALLOW_COPY_AND_ASSIGN(SokobanApp);
};

}   // namespace sokoban

#endif    //  SOKOBAN_APP_H