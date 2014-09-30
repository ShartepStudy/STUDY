#ifndef SOKOBAN_APP_H
#define SOKOBAN_APP_H

#include "game.h"
#include "map_creator.h"
#include "macros.h"

namespace sokoban {

class SokobanApp {
public:
  SokobanApp();
  ~SokobanApp() {};
  
  void Run();

private:
  Game game_;
  MapCreator map_creator_;

  DISALLOW_COPY_AND_ASSIGN(SokobanApp);
};

} //  namespace sokoban

#endif //  SOKOBAN_APP_H