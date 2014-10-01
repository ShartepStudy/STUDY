#include "sokoban_app.h"

#include <iostream>

namespace sokoban {

SokobanApp::SokobanApp():
    game_(),
    map_creator_()
{}

void SokobanApp::Run() {
  system("cls");

  size_t menu_number = 0;
  std::cout << "\n\t\t1. Play Game.\n\n\t\t2. Create Map. \n\n\t\tEnter your choice: ";
  std::cin >> menu_number;

  if (1 == menu_number) {
    int level_number = 0;
    std::cout << "\n\n\t\t Enter level number: ";
    std::cin >> level_number;

    std::string file_name("level-");
    file_name += std::to_string(level_number) + ".map";
    game_.Init(file_name);
    game_.Run();
  } else if (2 == menu_number) {
    map_creator_.Run();
  }

  std::cout << "\n\n\n\n\n\n\n\n";
}

} //  namespace sokoban
