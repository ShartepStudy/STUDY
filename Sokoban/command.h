#ifndef COMMAND_H
#define COMMAND_H

#include "macros.h"

#include "game_pole.h"

namespace sokoban {

class Command {
public:
  Command();
  virtual ~Command() {}
  
  virtual bool Execute() = 0;
  virtual bool UnExecute() = 0;

  static bool SetGamePole(GamePole* game_pole);
protected:
  bool ExecuteHelper(int dx, int dy);
  bool UnExecuteHelper(int dx, int dy);

  CellType GetCell(size_t x, size_t y) const { return (*game_pole_)[y][x]; }
  void SetCell(size_t x, size_t y, CellType data);

  int x_;
  int y_;

  bool with_box_;

  static GamePole* game_pole_;

private:
  DISALLOW_ASSIGN(Command);
};

}   // namespace sokoban

#endif    //  COMMAND_H