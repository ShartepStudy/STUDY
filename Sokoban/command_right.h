#ifndef COMMAND_RIGHT_H
#define COMMAND_RIGHT_H

#include "command.h"

namespace sokoban {

class CommandRight: public Command {
public:
  CommandRight(): Command(1,0) {}
  virtual ~CommandRight() {}

  //virtual bool Execute() { return ExecuteHelper(); }
  //virtual bool UnExecute() { return UnExecuteHelper(); }
};

}               //    namespace sokoban

#endif          //    COMMAND_RIGHT_H