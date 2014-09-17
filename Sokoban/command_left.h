#ifndef COMMAND_LEFT_H
#define COMMAND_LEFT_H

#include "command.h"

namespace sokoban {

class CommandLeft: public Command {
public:
  CommandLeft(): Command() {}
  virtual ~CommandLeft() {}

  virtual bool Execute() { return ExecuteHelper(-1, 0); }
  virtual bool UnExecute() { return UnExecuteHelper(-1, 0); }
};

}               //    namespace sokoban

#endif          //    COMMAND_LEFT_H