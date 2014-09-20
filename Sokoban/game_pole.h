#ifndef GAME_POLE_H
#define GAME_POLE_H

#include <vector>

#include "macros.h"
#include "sokoban_exception.h"

namespace sokoban {

enum CellType {
  MIN_CELL_TYPE = 0,
  EMPTY         = 1,
  PLAYER        = 2,
  BOX           = 3,
  FREE          = 4,
  WALL          = 5,
  NEXT_LINE     = 6,
  MAX_CELL_TYPE = 7
};

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

  std::vector<CellType>& operator[](size_t index) throw(GamePoleNotInitializeException);
  const std::vector< std::vector<CellType> >& operator()() const throw(GamePoleNotInitializeException);
  
  void DefaultInit();

private:
  std::vector< std::vector<CellType> > pole_;

  int x_;
  int y_;

  bool is_modify_;
  bool is_initialize_;

  DISALLOW_COPY_AND_ASSIGN(GamePole);
};

}   // namespace sokoban

#endif    //  GAME_POLE_H