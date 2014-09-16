#ifndef COMMAND_DOWN_H
#define COMMAND_DOWN_H

#include "command.h"

namespace sokoban {

class CommandDown: public Command {
public:
  CommandDown(): Command() {}
  virtual ~CommandDown() {}

  virtual bool Execute();
  virtual bool UnExecute();
};

}               //    namespace sokoban

#endif          //    COMMAND_DOWN_H