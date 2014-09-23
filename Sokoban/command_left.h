#ifndef COMMAND_LEFT_H
#define COMMAND_LEFT_H

#include "command.h"

namespace sokoban {

class CommandLeft: public Command {
public:
  CommandLeft(): Command(-1, 0) {}
  virtual ~CommandLeft() {}

  //virtual bool Execute() { return ExecuteHelper(); }
  //virtual bool UnExecute() { return UnExecuteHelper(); }
};

}               //    namespace sokoban

#endif          //    COMMAND_LEFT_H