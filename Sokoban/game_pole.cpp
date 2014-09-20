#include "game_pole.h"

#include <fstream>

namespace sokoban {

GamePole::GamePole():
    is_modify_(false),
    is_initialize_(false) 
{}

void GamePole::Init(char* file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) {
    throw OpenInputFileException("GamePole::Init", file_name);
  }

  int data;
  std::vector<CellType> vector_x;
  while (-1 != (data = file.get())) {
    if (NEXT_LINE == data) {
      pole_.push_back(vector_x);
      vector_x.clear();
    } else if (data > MIN_CELL_TYPE && data < MAX_CELL_TYPE) {
      vector_x.push_back(static_cast<CellType>(data));
      if (data == PLAYER) {
        x_ = vector_x.size() - 1;
        y_ = pole_.size();
      }
    } else {
      throw ReadWrongDataFromFileException("GamePole::Init", data);
    }
  }
  is_modify_ = true;
  is_initialize_ = true;
  file.close();
}

void GamePole::Save(char* file_name) {
  if (is_initialize_) {
    std::ofstream file(file_name);

    if (!file.is_open()) {
      throw OpenOutputFileException("GamePole::Save", file_name);
    }

    for (auto it_y: pole_) {
      for (auto it_x: it_y) {
        file << static_cast<char>(it_x);
      }
      file << static_cast<char>(NEXT_LINE);
    }
    file.close();
  }
}

bool GamePole::SetXY(int x, int y) {
  bool rv;
  if (is_initialize_) {
    rv = (PLAYER == pole_[y][x]);
  
    if (rv) {
      x_ = x;
      y_ = y;
    }
  } else {
    rv = false;
  }
  return rv;
}

std::vector<CellType>& GamePole::operator[](size_t index) { 
  if (!is_initialize_) {
    throw GamePoleNotInitializeException("GamePole::operator[]");
  }
  return pole_[index]; 
}

const std::vector< std::vector<CellType> >& GamePole::operator()() const {
  if (!is_initialize_) {
    throw GamePoleNotInitializeException("GamePole::operator()");
  }
  return pole_;
}

void GamePole::DefaultInit() {
  int arr[20][20] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 3, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  std::vector<CellType> vector_x;
  
  for (size_t i = 0; i < 20; i++) {
    for (size_t j = 0; j < 20; j++) {
      vector_x.push_back(static_cast<CellType>(arr[i][j]));
    }
    pole_.push_back(vector_x);
    vector_x.clear();
  }
  x_ = 9;
  y_ = 10;
  is_modify_ = true;
  is_initialize_ = true;
}

}   // namespace sokoban