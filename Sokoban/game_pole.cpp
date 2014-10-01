#define GAME_POLE_CPP
#include "game_pole.h"

namespace sokoban {

template<typename T>
GamePole<T>::GamePole() :
    pole_(),
    width_(0),
    height_(0),
    x_(0),
    y_(0),
    is_initialize_(false)
{}

template<typename T>
void GamePole<T>::Init(size_t width, size_t height, T data) {
  width_ = width; 
  height_ = height; 
  
  std::vector<T> vector_x(width, data);
  pole_.resize(height, vector_x);
}

template<typename T>
void GamePole<T>::SetXY(size_t x, size_t y) {
  if (PLAYER == pole_[y][x]) {
    x_ = x;
    y_ = y;
  }
}

template<typename T>
T GamePole<T>::GetCell(size_t x, size_t y) const {
  if (is_initialize_ && y < height_ && x < width_) {
    return pole_[y][x];
  } else {
    throw GamePoleNotInitializeException("GamePole::GetCell");
  }
}

template<typename T>
void GamePole<T>::SetCell(size_t x, size_t y, T data) {
  if (y < height_ && x < width_) {
    pole_[y][x] = data;
  } else {
    throw GamePoleNotInitializeException("GamePole::SetCell");
  }
}
//
//void GamePole::DefaultInit() {
//  int arr[20][20] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                      {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 5, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 5, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
//                      {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
//                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//  };
//
//  std::vector<CellType> vector_x;
//
//  for (size_t y = 0; y < 20; y++) {
//    for (size_t x = 0; x < 20; x++) {
//      vector_x.push_back(static_cast<CellType>(arr[y][x]));
//    }
//    pole_.push_back(vector_x);
//    vector_x.clear();
//  }
//  width_ = 20;
//  height_ = 20; 
//  is_initialize_ = true;
//}

}   // namespace sokoban