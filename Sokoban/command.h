#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "game_pole.h"
#include "macros.h"

namespace sokoban {

class CommandHelper {
public:
  virtual bool ExecuteHelper(GamePole* game_pole, int dx, int dy) = 0;
  virtual bool UnExecuteHelper(GamePole* game_pole, int x, int y) = 0;
};

class Command {
public:
  Command(int dx, int dy);
  virtual ~Command() {}
  
  bool Execute() { return command_helper_->ExecuteHelper(game_pole_, dx_, dy_); }
  bool UnExecute() { return command_helper_->UnExecuteHelper(game_pole_, x_, y_); }

  static bool SetGamePole(GamePole* game_pole);

protected:
  int x_;
  int y_;

  int dx_;
  int dy_;

private:
  static GamePole* game_pole_;

  std::shared_ptr<CommandHelper> command_helper_;

  DISALLOW_ASSIGN(Command);
};

}   // namespace sokoban

#endif    //  COMMAND_H