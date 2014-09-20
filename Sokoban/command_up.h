#ifndef COMMAND_UP_H
#define COMMAND_UP_H

#include "command.h"

namespace sokoban {

class CommandUp: public Command {
public:
  CommandUp(): Command() {}
  virtual ~CommandUp() {}

  virtual bool Execute() { return ExecuteHelper(0, -1); }
  virtual bool UnExecute() { return UnExecuteHelper(0, -1); }
};

}               //    namespace sokoban

#endif          //    COMMAND_UP_H