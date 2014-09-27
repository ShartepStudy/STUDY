#ifndef SOKOBAN_APP_H
#define SOKOBAN_APP_H

#include <stack>
#include <memory>

#include "macros.h"
#include "game_pole.h"
//#include "renderer.h"

namespace sokoban {

class Command;

enum ButtonCode {
  UP_BUTTON           = 72,
  LEFT_BUTTON         = 75,
  RIGHT_BUTTON        = 77,
  DOWN_BUTTON         = 80,
  R_BUTTON            = 82,
  U_BUTTON            = 85,
  r_BUTTON            = 114,
  u_BUTTON            = 117,
  EXTENDED_BUTTONS    = 224
};

class SokobanApp {
public:
  SokobanApp();
  ~SokobanApp() {};
  
  bool Init(const std::string& file_name);
  void Run();

private:
//  void UndoHelper(std::shared_ptr<Command>& command);

  GamePole base_map_;
  GamePole objects_map_;

//  Renderer renderer_;
//  std::stack<std::shared_ptr<Command> > undo_commands_;
//  std::stack<std::shared_ptr<Command> > redo_commands_;

  DISALLOW_COPY_AND_ASSIGN(SokobanApp);
};

}   // namespace sokoban

#endif    //  SOKOBAN_APP_H