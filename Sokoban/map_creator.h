#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include "button_code.h"
#include "game_pole.h"
#include "renderer.h"
#include "sokoban_exception.h"

namespace sokoban {

class MapCreator {
 public:
  MapCreator(Renderer* renderer);
  ~MapCreator();

  void Run();

 private:
  bool InitSize();
  void SaveMap(const std::string& file_name) const throw (OpenOutputFileException);

  size_t width_;
  size_t height_;

  GamePole<CellType> base_map_;
  GamePole<CellType> objects_map_;
  Renderer* renderer_;
};

}  // namespace sokoban 

#endif  // MAP_CREATOR_H