#ifndef COMMAND_DOWN_H
#define COMMAND_DOWN_H

#include "command.h"

namespace sokoban {

class CommandDown: public Command {
public:
  CommandDown(): Command() {}
  virtual ~CommandDown() {}

  virtual bool Execute() { return ExecuteHelper(0, 1); }
  virtual bool UnExecute() { return UnExecuteHelper(0, 1); }
};

}               //    namespace sokoban

#endif          //    COMMAND_DOWN_H