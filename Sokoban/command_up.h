#ifndef COMMAND_UP_H
#define COMMAND_UP_H

#include "command.h"

namespace sokoban {

class CommandUp: public Command {
public:
  CommandUp(): Command(0, -1) {}
  virtual ~CommandUp() {}

  //virtual bool Execute() { return ExecuteHelper(); }
  //virtual bool UnExecute() { return UnExecuteHelper(); }
};

}               //    namespace sokoban

#endif          //    COMMAND_UP_H