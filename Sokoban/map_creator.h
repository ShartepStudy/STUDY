#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include "game_pole.h"
#include "renderer.h"

namespace sokoban {

class MapCreator {
 public:
  MapCreator();
  ~MapCreator();

  void Run();

 private:
  bool InitSize();

  size_t width_;
  size_t height_;

  GamePole<CellType> base_map_;
  GamePole<CellType> objects_map_;
  Renderer renderer_;
};

}  // namespace sokoban 

#endif  // MAP_CREATOR_H