#ifndef SOKOBAN_EXCEPTION_H
#define SOKOBAN_EXCEPTION_H

#include <exception>
#include <string>

namespace sokoban {

class SokobanException: std::exception {
public:
  SokobanException(std::string& error):
    exception(),
    error_data_(error)
  {}

  virtual const char* what() const throw() {
    return error_data_.c_str();
  }
private:
  std::string error_data_;
};

class OpenInputFileException: SokobanException {
public:
  OpenInputFileException(std::string error_place, std::string file_name):
    SokobanException(error_place + "  Error!  Can't open file " + file_name) {}
};

class ReadWrongDataFromFileException: SokobanException {
public:
  ReadWrongDataFromFileException(std::string error_place, int wrong_data_from_file):
    SokobanException(error_place + "  Error!  Data (" + 
      std::to_string(wrong_data_from_file) + ") from file is wrong! They doesn't conform CellType!") {}
};

class OpenOutputFileException: SokobanException {
public:
  OpenOutputFileException(std::string error_place, std::string file_name):
    SokobanException(error_place + "  Error!  Can't open file " + file_name) {}
};

class GamePoleNotInitializeException: SokobanException {
public:
  GamePoleNotInitializeException(std::string error_place):
    SokobanException(error_place + "  Error!  GamePole not initialize yet, you should call game_pole.Init()") {}
};

//class SetPlayerCoordinatesException: SokobanException{
//public:
//  SetPlayerCoordinatesException(std::string error_place, int cell_type_by_setted_coordinates) :
//    SokobanException(error_place + 
//      "  Error!  You try to set wrong coordinates of player. CellType of setted coordinates is " +
//      std::to_string(cell_type_by_setted_coordinates)) {}
//};

}           //    namespace sokoban

#endif      //    SOKOBAN_EXCEPTION_H