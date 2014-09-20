#ifndef COMMAND_RIGHT_H
#define COMMAND_RIGHT_H

#include "command.h"

namespace sokoban {

class CommandRight: public Command {
public:
  CommandRight(): Command() {}
  virtual ~CommandRight() {}

  virtual bool Execute() { return ExecuteHelper(1, 0); }
  virtual bool UnExecute() { return UnExecuteHelper(1, 0); }
};

}               //    namespace sokoban

#endif          //    COMMAND_RIGHT_H