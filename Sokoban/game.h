#ifndef GAME_APP_H
#define GAME_APP_H

#include <stack>
#include <memory>
#include <string>

#include "game_pole.h"
#include "macros.h"
#include "renderer.h"

namespace sokoban {

class Command;
class Renderer;

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

class Game {
public:
  Game();
  ~Game() {}
  
  void Init(const std::string& file_name) throw (OpenInputFileException, ReadWrongDataFromFileException);
  void Run();

private:
  void UndoHelper(std::shared_ptr<Command>& command);
  bool IsFinish();
  void LevelComplete();

  GamePole<CellType> base_map_;
  GamePole<CellType> objects_map_;

  Renderer renderer_;
  std::stack<std::shared_ptr<Command> > undo_commands_;
  std::stack<std::shared_ptr<Command> > redo_commands_;

  DISALLOW_COPY_AND_ASSIGN(Game);
};

} //  namespace sokoban

#endif //  GAME_APP_H