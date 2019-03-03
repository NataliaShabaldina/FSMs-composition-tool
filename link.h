#ifndef LINK_H
#define LINK_H

#include "fsm.h"

/// @brief Класс связи как логического элемента
class Link
{
private:
     QString id_;
     Fsm inputFsm_;
     Fsm outputFsm_;

public:
     Link(QString id = "", Fsm inputFsm = Fsm(), Fsm outputFsm = Fsm());

     QString getId() const;
     Fsm getInputFsm() const;
     Fsm getOutputFsm() const;
};

#endif // LINK_H
