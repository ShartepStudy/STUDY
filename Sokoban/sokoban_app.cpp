#include "sokoban_app.h"

namespace sokoban {

SokobanApp::SokobanApp():
    game_(),
    map_creator_()
{}

void SokobanApp::Run() {
  //game_.Init("level_8.dat");
  //game_.Run();
  map_creator_.Run();
}

}   // namespace sokoban
