#ifndef COMMAND_DOWN_H
#define COMMAND_DOWN_H

#include "command.h"

namespace sokoban {

class CommandDown: public Command {
public:
  CommandDown(): Command(0, 1) {}
  virtual ~CommandDown() {}

  //virtual bool Execute() { return ExecuteHelper(); }
  //virtual bool UnExecute() { return UnExecuteHelper(); }
};

}               //    namespace sokoban

#endif          //    COMMAND_DOWN_H