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

  char data;
  std::vector<CellType> vector_x;
  while (data = file.get()) {
    if ('\n' == data) {
      pole_.push_back(vector_x);
      vector_x.clear();
    } else if (data > MIN_CELL_TYPE && data < MAX_CELL_TYPE) {
      vector_x.push_back(static_cast<CellType>(data));
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

    for (auto it_y = std::begin(pole_); it_y != std::end(pole_); ++it_y) {
      for (auto it_x = std::begin(*it_y); it_x != std::end(*it_y); ++it_x) {
        file << static_cast<char>(*it_x);
      }
      file << '\n';
    }
    file.close();
  }
}

bool GamePole::SetXY(int x, int y) {
  bool rv;
  if (is_initialize_) {
    rv = (PLAYER == pole_[x][y]);
  
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
    throw GamePoleNotInitializeException("GamePole::operator[]");
  }
  return pole_;
}

}   // namespace sokoban