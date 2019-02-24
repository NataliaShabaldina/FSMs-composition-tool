#ifndef LINK_H
#define LINK_H

#include "fsm.h"

class Link
{
public:
     Link();

     QString getName() const;
     Fsm getInputFsm() const;
     Fsm getOutputFsm() const;

private:
     Fsm inputFsm_;
     Fsm outputFsm_;
     QString name_;
};

#endif // LINK_H
