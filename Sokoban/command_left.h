#ifndef COMMAND_LEFT_H
#define COMMAND_LEFT_H

#include "command.h"

namespace sokoban {

class CommandLeft: public Command {
public:
  CommandLeft(): Command() {}
  virtual ~CommandLeft() {}

  virtual bool Execute();
  virtual bool UnExecute();
};

}               //    namespace sokoban

#endif          //    COMMAND_LEFT_H