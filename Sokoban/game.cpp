#include "game.h"

#include <conio.h>
#include <fstream>

#include "command.h"
#include "command_down.h"
#include "command_left.h"
#include "command_right.h"
#include "command_up.h"

namespace sokoban {

Game::Game():
    base_map_(),
    objects_map_(),
    renderer_(base_map_, objects_map_),
    undo_commands_(),
    redo_commands_(),
    step_count_(0)
{
  Command::SetGamePole(&base_map_, &objects_map_);
}

void Game::Init(const std::string& file_name) {
  std::ifstream file(file_name.c_str());
  
  if (!file.is_open()) {
    throw OpenInputFileException("GamePole::Init", file_name);
  }
  
  int d;
  size_t width, height;
  if (-1 != (d = file.get())) width = d;
  if (-1 != (d = file.get())) height = d;
  base_map_.Init(width, height, EMPTY);
  objects_map_.Init(width, height, EMPTY);

  CellType data;
  int x = 0, y = 0;
  
  while (-1 != (data = static_cast<CellType>(file.get()))) {
    if (NEXT_LINE == data) {
      ++y;
      x = 0;
    } else if (data > MIN_CELL_TYPE && data < MAX_CELL_TYPE) {
      if (PLAYER == data) {
        objects_map_.SetCell(x, y, data);
        base_map_.SetCell(x, y, FREE);
        objects_map_.SetXY(x, y);
      } else if (BOX == data) {
        objects_map_.SetCell(x, y, data);
        base_map_.SetCell(x, y, FREE);
      } else {
        base_map_.SetCell(x, y, data);
      }
      ++x;
    } else {
      throw ReadWrongDataFromFileException("GamePole::Init", data);
    }
  }
  file.close();
  base_map_.SetInitialize(true);
  objects_map_.SetInitialize(true);
  renderer_.Init();
}

void Game::Run() {
  renderer_.Show();
  do {
    Sleep(10);

    std::shared_ptr<Command> command;
    
    int btnCode = getch();
    if (EXTENDED_BUTTONS == btnCode) {
      btnCode = getch();
    }

    switch (btnCode) {
    case UP_BUTTON: 
      command.reset(new CommandUp());
      UndoHelper(command);
      break;
    case DOWN_BUTTON: 
      command.reset(new CommandDown());
      UndoHelper(command);
      break;
    case LEFT_BUTTON: 
      command.reset(new CommandLeft());
      UndoHelper(command);
      break;
    case RIGHT_BUTTON: 
      command.reset(new CommandRight());
      UndoHelper(command);
      break;
    case U_BUTTON:
    case u_BUTTON:
      if (!undo_commands_.empty()) {
        command = undo_commands_.top();
        undo_commands_.pop();
        command->UnExecute();
        redo_commands_.push(command);
        --step_count_;
      }
      break;
    case R_BUTTON:
    case r_BUTTON:
      if (!redo_commands_.empty()) {
        command = redo_commands_.top();
        redo_commands_.pop();
        command->Execute();
        undo_commands_.push(command);
        ++step_count_;
      }
      break;
    }

    renderer_.Show();
  } while(!IsFinish());

  LevelComplete();
}

void Game::UndoHelper(std::shared_ptr<Command>& command) {
  if (command->Execute()) {
    undo_commands_.push(command);
    if (!redo_commands_.empty()) {
      redo_commands_ = std::stack<std::shared_ptr<Command> >();
    }
    ++step_count_;
  }
}

bool Game::IsFinish() {
  for (size_t y = 0; y < base_map_.GetHeight(); ++y) {
    for (size_t x = 0; x < base_map_.GetWidth(); ++x) {
      if (BOX == objects_map_.GetCell(x, y) && BOX_PLACE != base_map_.GetCell(x, y)) {
        return false;
      }
    }
  }
  return true;
}

void Game::LevelComplete() {
  printf("\n\n\n\n\tYOU WIN !!! You made %d steps! To continue press any key.\n", step_count_);
  getch();
}

} //  namespace sokoban
