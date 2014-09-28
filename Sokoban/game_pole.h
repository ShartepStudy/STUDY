#ifndef GAME_POLE_H
#define GAME_POLE_H

//#include <utility>
#include <vector>
//#include <windows.h>

#include "macros.h"
#include "sokoban_exception.h"

namespace sokoban {

enum CellType {
  MIN_CELL_TYPE       = -1,
  EMPTY               = 0,
  PLAYER              = 1,
  BOX                 = 2,
  FREE                = 3,
  WALL                = 4,
  BOX_PLACE           = 5,
  PLAYER_ON_BOX_PLACE = 6,
  BOX_ON_BOX_PLACE    = 7,
  MAX_CELL_TYPE       = 8,
  NEXT_LINE           = 9
};

template<typename T>
class GamePole {
public:
  GamePole();
  ~GamePole() {}

//  void Init(char* file_name) throw(OpenInputFileException, ReadWrongDataFromFileException);
  //void Save(char* file_name) throw(OpenOutputFileException);

  //bool IsModify() { return is_modify_; }
  //void SetModify() { is_modify_ = true; }
  //void SetUnModify() { is_modify_ = false; }
  void SetInitialize(bool is_initialize) { is_initialize_ = is_initialize; }

  //int X() const { return x_; }
  //int Y() const { return y_; }
  //bool SetXY(int x, int y);

  void Init(size_t width, size_t height, T data);
  size_t GetWidth() const { return width_; }
  size_t GetHeight() const { return height_; }

  T GetCell(size_t x, size_t y) const throw(GamePoleNotInitializeException); 
  void SetCell(size_t x, size_t y, T data) throw(GamePoleNotInitializeException);

  //std::vector<CellPair>& operator[](size_t index) throw(GamePoleNotInitializeException);
  //const std::vector< std::vector<CellPair> >& operator()() const throw(GamePoleNotInitializeException);
  
  //void DefaultInit();

private:
  std::vector< std::vector<T> > pole_;

  size_t width_;
  size_t height_;

//  bool is_modify_;
  bool is_initialize_;

  DISALLOW_COPY_AND_ASSIGN(GamePole);
};

}   // namespace sokoban

#ifndef GAME_POLE_CPP
#include "game_pole.cpp"
#endif

#endif    //  GAME_POLE_H

