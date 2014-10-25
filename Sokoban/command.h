#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "game_pole.h"
#include "macros.h"

namespace sokoban {

class Command {
public:
  Command();
  virtual ~Command() {}
  
  virtual bool Execute() = 0;
  virtual bool UnExecute() = 0;

  static void SetGamePole(GamePole<CellType>* base_map, GamePole<CellType>* objects_map);

protected:
  bool ExecuteHelper(int dx, int dy);
  bool UnExecuteHelper(int dx, int dy);

  static GamePole<CellType>* base_map_;
  static GamePole<CellType>* objects_map_;

  size_t x_;
  size_t y_;

  bool with_box_;

private:
  DISALLOW_ASSIGN(Command);
};

} //  namespace sokoban

#endif //  COMMAND_H