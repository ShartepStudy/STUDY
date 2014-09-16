#ifndef COMMAND_RIGHT_H
#define COMMAND_RIGHT_H

#include "command.h"

namespace sokoban {

class CommandRight: public Command {
public:
  CommandRight(): Command() {}
  virtual ~CommandRight() {}

  virtual bool Execute();
  virtual bool UnExecute();
};

}               //    namespace sokoban

#endif          //    COMMAND_RIGHT_H