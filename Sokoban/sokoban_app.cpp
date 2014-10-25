#include "sokoban_app.h"

#include <conio.h>
#include <iostream>

#include "button_code.h"

namespace sokoban {

SokobanApp::SokobanApp():
    renderer_()
{}

void SokobanApp::Run() {
  bool is_finish = false;

  do {
    system("cls");

    size_t menu_number;
    std::cout << "\n\n\t\t1. Play Game.\n\n\t\t2. Create Map. \n\n\t\t3. Exit.\n\n\t\tEnter your choice: ";
    std::cin >> menu_number;
    getchar();

    if (1 == menu_number) {
      int level_number = 0;
      std::string file_name("level-");
      std::cout << "\n\n\t\tEnter level number: ";
      std::cin >> level_number;
      getchar();
      system("cls");

      file_name += std::to_string(level_number) + ".map";
      
      Game game(&renderer_);
      game.Init(file_name);
      game.Run();
    } else if (2 == menu_number) {
      MapCreator map_creator(&renderer_);
      map_creator.Run();
    } else if (3 == menu_number) {
      is_finish = true;
    } else {
      std::cout << "\n\n\t\tWrong menu number! Try again.";
      Sleep(2000);
    }
  } while (!is_finish);
  std::cout << "\n\n\n\n\n\n\n\n";
}

} //  namespace sokoban
