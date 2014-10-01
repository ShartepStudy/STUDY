#ifndef GAME_APP_H
#define GAME_APP_H

#include <stack>
#include <memory>
#include <string>

#include "button_code.h"
#include "game_pole.h"
#include "macros.h"
#include "renderer.h"

namespace sokoban {

class Command;
class Renderer;

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