#include "game_pole.h"

#include <fstream>

namespace sokoban {

GamePole::GamePole():
    is_modify_(false),
    is_initialize_(false),
    width_(0),
    height_(0)
{}

void GamePole::Init(char* file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) {
    throw OpenInputFileException("GamePole::Init", file_name);
  }

  int data, x = 0, y = 0;
  const int img_step = 30;
  std::vector<CellPair> vector_x;
  HWND hConsole = GetConsoleWindow();
  int Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

  while (-1 != (data = file.get())) {
    if (NEXT_LINE == data) {
      pole_.push_back(vector_x);
      if (vector_x.size() > width_) {
        width_ = vector_x.size();
      }
      vector_x.clear();
      ++y;
      x = 0;
    } else if (data > MIN_CELL_TYPE && data < MAX_CELL_TYPE) {
      HWND hWnd = CreateWindowEx(0,
                                 L"static",
                                 NULL,
                                 Style,
                                 x*img_step,
                                 y*img_step,
                                 0,
                                 0,
                                 hConsole,
                                 (HMENU)((y + 1)*(x + 1)),
                                 GetModuleHandle(0),
                                 NULL);
      vector_x.push_back(CellPair(static_cast<CellType>(data), hWnd));
      ++x;
      if (data == PLAYER) {
        x_ = vector_x.size() - 1;
        y_ = pole_.size();
      }
    } else {
      throw ReadWrongDataFromFileException("GamePole::Init", data);
    }
  }
  height_ = pole_.size();
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
        file << static_cast<char>(it_x.first);
      }
      file << static_cast<char>(NEXT_LINE);
    }
    file.close();
  }
}

bool GamePole::SetXY(int x, int y) {
  bool rv;
  if (is_initialize_) {
    rv = (PLAYER == pole_[y][x].first || PLAYER_ON_BOX_PLACE == pole_[y][x].first);
  
    if (rv) {
      x_ = x;
      y_ = y;
    }
  } else {
    rv = false;
  }
  return rv;
}

void GamePole::SetCell(size_t x, size_t y, CellType data) {
  if (is_initialize_) {
    pole_[y][x].first = data;
  
    if (PLAYER == data || PLAYER_ON_BOX_PLACE == data) {
      SetXY(x, y);
    }
  }
}


std::vector<CellPair>& GamePole::operator[](size_t index) {
  if (!is_initialize_) {
    throw GamePoleNotInitializeException("GamePole::operator[]");
  }
  return pole_[index]; 
}

const std::vector< std::vector<CellPair> >& GamePole::operator()() const {
  if (!is_initialize_) {
    throw GamePoleNotInitializeException("GamePole::operator()");
  }
  return pole_;
}

void GamePole::DefaultInit() {
  int arr[20][20] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 5, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 4, 0},
                      {0, 4, 3, 5, 5, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0},
                      {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  const int img_step = 30;
  std::vector<CellPair> vector_x;
  HWND hConsole = GetConsoleWindow(); 
  int Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

  for (size_t y = 0; y < 20; y++) {
    for (size_t x = 0; x < 20; x++) {
      HWND hWnd = CreateWindowEx(0,
                                 L"static",
                                 NULL,
                                 Style,
                                 x*img_step,
                                 y*img_step,
                                 0,
                                 0,
                                 hConsole,
                                 (HMENU)((y + 1)*(x + 1)),
                                 GetModuleHandle(0),
                                 NULL);
      vector_x.push_back(CellPair(static_cast<CellType>(arr[y][x]), hWnd));
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