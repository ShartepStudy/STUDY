#include "sokoban_app.h"

//#include <conio.h>
#include <fstream>

//#include "command.h"
//#include "command_down.h"
//#include "command_left.h"
//#include "command_right.h"
//#include "command_up.h"

namespace sokoban {

SokobanApp::SokobanApp():
    base_map_(),
    objects_map_(),
    //game_pole_(),
    renderer_(base_map_, objects_map_)
    //undo_commands_(),
    //redo_commands_()
{
//  Command::SetGamePole(&game_pole_);
}

bool SokobanApp::Init(const std::string& file_name) {
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
//  const int img_step = 30;
//  std::vector<CellType> vector_x;
//  HWND hConsole = GetConsoleWindow();
//  int Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;
  
  while (-1 != (data = static_cast<CellType>(file.get()))) {
    if (NEXT_LINE == data) {
      //pole_.push_back(vector_x);
      //if (vector_x.size() > width_) {
      //  width_ = vector_x.size();
      //}
      //vector_x.clear();
      ++y;
      x = 0;
    } else if (data > MIN_CELL_TYPE && data < MAX_CELL_TYPE) {
      base_map_.SetCell(x, y, data);
      
      if (PLAYER == data || BOX == data) {
        objects_map_.SetCell(x, y, data);
      }
      //HWND hWnd = CreateWindowEx(0,
      //                            L"static",
      //                            NULL,
      //                            Style,
      //                            x*img_step,
      //                            y*img_step,
      //                            0,
      //                            0,
      //                            hConsole,
      //                            (HMENU)((y + 1)*(x + 1)),
      //                            GetModuleHandle(0),
      //                            NULL);
      //vector_x.push_back(static_cast<CellType>(data));
      //vector_x.push_back(CellPair(static_cast<CellType>(data), hWnd));
      ++x;
      //if (data == PLAYER) {
      //  x_ = vector_x.size() - 1;
      //  y_ = pole_.size();
      //}
    } else {
      throw ReadWrongDataFromFileException("GamePole::Init", data);
    }
  }
  file.close();
  //height_ = pole_.size();
  //is_modify_ = true;
  base_map_.SetInitialize(true);
  objects_map_.SetInitialize(true);
  renderer_.Init();
}

void SokobanApp::Run() {
  //base_map_.DefaultInit();
  //base_map_.Save("level_8.dat");
  do {
    Sleep(100);
    renderer_.Show();

  //  std::shared_ptr<Command> command;
  //  
  //  int btnCode = getch();
  //  if (EXTENDED_BUTTONS == btnCode) {
  //    btnCode = getch();
  //  }

  //  switch (btnCode) {
  //  case UP_BUTTON: 
  //    command.reset(new CommandUp);
  //    UndoHelper(command);
  //    break;
  //  case DOWN_BUTTON: 
  //    command.reset(new CommandDown);
  //    UndoHelper(command);
  //    break;
  //  case LEFT_BUTTON: 
  //    command.reset(new CommandLeft);
  //    UndoHelper(command);
  //    break;
  //  case RIGHT_BUTTON: 
  //    command.reset(new CommandRight);
  //    UndoHelper(command);
  //    break;
  //  case U_BUTTON:
  //  case u_BUTTON:
  //    if (!undo_commands_.empty()) {
  //      command = undo_commands_.top();
  //      undo_commands_.pop();
  //      command->UnExecute();
  //      redo_commands_.push(command);
  //    }
  //    break;
  //  case R_BUTTON:
  //  case r_BUTTON:
  //    if (!redo_commands_.empty()) {
  //      command = redo_commands_.top();
  //      redo_commands_.pop();
  //      command->Execute();
  //      undo_commands_.push(command);
  //    }
  //    break;
  //  }

  } while(true);
}
//
//void SokobanApp::UndoHelper(std::shared_ptr<Command>& command) {
//  if (command->Execute()) {
//    undo_commands_.push(command);
//    if (!redo_commands_.empty()) {
//      redo_commands_ = std::stack<std::shared_ptr<Command> >();
//    }
//  }
//}

}   // namespace sokoban
