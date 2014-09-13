#ifndef _IBOT_H_
#define _IBOT_H_

class IBot
{
public:
   IBot() {};
   virtual ~IBot() {};
public:
   virtual void execute() = 0;
};

#endif

