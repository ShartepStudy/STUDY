#ifndef COMMAND_UP_H
#define COMMAND_UP_H

#include "command.h"

namespace sokoban {

class CommandUp: public Command {
public:
  CommandUp(): Command() {}
  virtual ~CommandUp() {}

  virtual bool Execute();
  virtual bool UnExecute();
};

}               //    namespace sokoban

#endif          //    COMMAND_UP_H