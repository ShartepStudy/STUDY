#include "map_creator.h"

#include <iostream>
#include <conio.h>

namespace sokoban {

MapCreator::MapCreator():
    width_(0),
    height_(0),
    base_map_(),
    objects_map_(),
    renderer_(base_map_, objects_map_)
{}

MapCreator::~MapCreator() {}

void MapCreator::Run() {
  if (!InitSize()) {
    std::cout << "You enter wrong data more then 3 times! Exit from Map Creation!\n";
  } else {
    base_map_.Init(width_, height_, EMPTY);
    base_map_.SetInitialize(true);
    objects_map_.Init(width_, height_, EMPTY);
    objects_map_.SetInitialize(true);
    renderer_.Init();
    renderer_.Show();
    
    do {
      Sleep(50);

      renderer_.Show();
    } while (true);
  }
}

bool MapCreator::InitSize() {
  int i = 0;
  do {
    if (i > 0) {
      std::cout << "\nYou enter wrong data try again!\n";
    }
    std::cout << "\nEnter map width 5-50: ";
    std::cin >> width_;
    ++i;
  } while (!(width_ >= 5 && width_ <= 50) && i < 3);

  if (i >= 3) return false;

  i = 0;
  do {
    if (i > 0) {
      std::cout << "\nYou enter wrong data try again!\n";
    }
    std::cout << "\nEnter map height 5-50: ";
    std::cin >> height_;
    ++i;
  } while (!(height_ >= 5 && height_ <= 50) && i < 3);

  if (i >= 3) return false;
  return true;
}

}  // namespace sokoban