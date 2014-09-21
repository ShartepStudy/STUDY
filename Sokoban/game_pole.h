#ifndef GAME_POLE_H
#define GAME_POLE_H

#include <utility>
#include <vector>
#include <windows.h>

#include "macros.h"
#include "sokoban_exception.h"

namespace sokoban {

enum CellType {
  MIN_CELL_TYPE = -1,
  EMPTY         = 0,
  PLAYER        = 1,
  BOX           = 2,
  FREE          = 3,
  WALL          = 4,
  BOX_PLACE     = 5,
  MAX_CELL_TYPE = 6,
  NEXT_LINE     = 7
};

typedef std::pair<CellType, HWND> CellPair;

class GamePole {
public:
  GamePole();
  ~GamePole() {}

  void Init(char* file_name) throw(OpenInputFileException, ReadWrongDataFromFileException);
  void Save(char* file_name) throw(OpenOutputFileException);

  bool IsModify() { return is_modify_; }
  void SetModify() { is_modify_ = true; }
  void SetUnModify() { is_modify_ = false; }

  int X() const { return x_; }
  int Y() const { return y_; }
  bool SetXY(int x, int y);

  size_t GetWidth() const { return width_; }
  size_t GetHeight() const { return height_; }

  std::vector<CellPair>& operator[](size_t index) throw(GamePoleNotInitializeException);
  const std::vector< std::vector<CellPair> >& operator()() const throw(GamePoleNotInitializeException);
  
  void DefaultInit();

private:
  std::vector< std::vector<CellPair> > pole_;

  int x_;
  int y_;

  size_t width_;
  size_t height_;

  bool is_modify_;
  bool is_initialize_;

  DISALLOW_COPY_AND_ASSIGN(GamePole);
};

}   // namespace sokoban

#endif    //  GAME_POLE_H