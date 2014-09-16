#ifndef RENDERER_H
#define RENDERER_H

#include "macros.h"

namespace sokoban {

class GamePole;
  
class Renderer {
public:
  Renderer(GamePole& game_pole): game_pole_(game_pole) {};
  ~Renderer() {};

  void Show();

private:
  GamePole& game_pole_;

  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

}           //    namespace sokoban

#endif      //    RENDERER_H