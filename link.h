#ifndef LINK_H
#define LINK_H

#include "fsm.h"

class Link
{
public:
     Link(QString id = "", Fsm inputFsm = Fsm(), Fsm outputFsm = Fsm());

     QString getId() const;
     Fsm getInputFsm() const;
     Fsm getOutputFsm() const;

private:
     QString id_;
     Fsm inputFsm_;
     Fsm outputFsm_;
};

#endif // LINK_H
