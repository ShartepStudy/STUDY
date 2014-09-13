#ifndef COMMAND_H
#define COMMAND_H

#include "macros.h"

namespace sokoban {

class GamePole;

class Command {
public:
  Command() {}
  ~Command() {}
  
  virtual bool Execute() const = 0;
  virtual bool UnExecute() const = 0;

  static bool SetGamePole(GamePole* game_pole);
private:
  static GamePole* game_pole_;

  int start_x_;
  int start_y_;

  bool with_box_;

  DISALLOW_ASSIGN(Command);
};

}   // namespace sokoban

#endif    //  COMMAND_H