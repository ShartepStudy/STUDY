#include "map_creator.h"

#include <fstream>
#include <iostream>
#include <conio.h>

namespace sokoban {

MapCreator::MapCreator(Renderer* renderer):
    width_(0),
    height_(0),
    base_map_(),
    objects_map_(),
    renderer_(renderer)
{}

MapCreator::~MapCreator() {}

void MapCreator::Run() {
  if (!InitSize()) {
    std::cout << "\n\n\tYou enter wrong data more then 3 times! Exit from Map Creation!\n";
  } else {
    system("cls");
    base_map_.Init(width_, height_, EMPTY);
    base_map_.SetInitialize(true);
    objects_map_.Init(width_, height_, EMPTY);
    objects_map_.SetInitialize(true);
    renderer_->Init(&base_map_, &objects_map_);
    renderer_->Show();
    
    bool is_finish = false;
    CellType cell_type = EMPTY;
    size_t x = 0, y = 0;
    do {
      Sleep(10);

      int btnCode = _getch();
      if (EXTENDED_BUTTONS == btnCode) {
        btnCode = _getch();
      }

      switch (btnCode) {
      case ENTER_BUTTON:
        if (PLAYER == cell_type || BOX == cell_type) {
          objects_map_.SetCell(x, y, cell_type);
        } else {
          base_map_.SetCell(x, y, cell_type);
          if (objects_map_.GetCell(x, y) != EMPTY) {
            objects_map_.SetCell(x, y, EMPTY);
          }
        }
        break;
      case SPACE_BUTTON:
        cell_type = static_cast<CellType>(static_cast<int>(cell_type)+1);
        if (PLAYER_ON_BOX_PLACE == cell_type) cell_type = EMPTY;
        break;
      case UP_BUTTON:
        if (y) --y;
        break;
      case DOWN_BUTTON:
        if (y < base_map_.GetHeight()-1) ++y;
        break;
      case LEFT_BUTTON:
        if (x) --x;
        break;
      case RIGHT_BUTTON:
        if (x < base_map_.GetWidth()-1) ++x;
        break;
      case ESC_BUTTON:
        is_finish = true;
        break;
      }

      renderer_->Show();
      renderer_->ShowCell(x, y, cell_type);
    } while (!is_finish);
  }

  renderer_->ClearScreen();
 
  std::cout << "\n\n\t\tEnter level number : ";
  std::string file_name("level-");
  int n = 0;
  std::cin >> n;
  getchar();
  file_name.append(std::to_string(n) + ".map");
  SaveMap(file_name);
}

bool MapCreator::InitSize() {
  int i = 0;
  do {
    if (i > 0) {
      std::cout << "\n\n\t\tYou enter wrong data try again!\n";
    }
    std::cout << "\n\n\t\tEnter map width 5-30: ";
    std::cin >> width_;
    ++i;
  } while (!(width_ >= 5 && width_ <= 30) && i < 3);

  if (i >= 3) return false;

  i = 0;
  do {
    if (i > 0) {
      std::cout << "\n\n\t\tYou enter wrong data try again!\n";
    }
    std::cout << "\n\n\t\tEnter map height 5-30: ";
    std::cin >> height_;
    ++i;
  } while (!(height_ >= 5 && height_ <= 30) && i < 3);

  if (i >= 3) return false;
  return true;
}

void MapCreator::SaveMap(const std::string& file_name) const {
  std::ofstream file(file_name);
  
  if (!file.is_open()) {
    throw OpenOutputFileException("MapCreator::SaveMap", file_name);
  }
  
  file << static_cast<char>(base_map_.GetWidth());
  file << static_cast<char>(base_map_.GetHeight());
  
  CellType cell_type;
  for (size_t y = 0; y < base_map_.GetHeight(); y++) {
    for (size_t x = 0; x < base_map_.GetWidth(); x++) {
      cell_type = objects_map_.GetCell(x,y);
      if (EMPTY == cell_type) {
        cell_type = base_map_.GetCell(x, y);
      }
      file << static_cast<char>(cell_type);
    }
    file << static_cast<char>(NEXT_LINE);
  }

  file.close();
}

}  // namespace sokoban