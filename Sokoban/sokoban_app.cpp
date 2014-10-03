#include "sokoban_app.h"

#include <conio.h>
#include <iostream>

#include "button_code.h"

namespace sokoban {

SokobanApp::SokobanApp():
    game_(),
    map_creator_()
{}

void SokobanApp::Run() {
  bool is_finish = false;

  do {
    system("cls");

    size_t menu_number;
    std::cout << "\n\t\t1. Play Game.\n\n\t\t2. Create Map. \n\n\t\t3. Exit.\n\n\t\tEnter your choice: ";
    menu_number = getch();

    int level_number = 0;
    std::string file_name("level-");
    switch (menu_number) {
    case ONE_BUTTON:
      std::cout << "\n\n\t\t Enter level number: ";
      level_number = getch();

      file_name += std::to_string(level_number-48) + ".map";
      game_.Init(file_name);
      game_.Run();
      break;
    case TWO_BUTTON:
      map_creator_.Run();
      break;
    case THREE_BUTTON:
      is_finish = true;
      break;
    }
  } while (!is_finish);
  std::cout << "\n\n\n\n\n\n\n\n";
}

} //  namespace sokoban
