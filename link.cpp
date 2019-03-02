#include "link.h"

Link::Link(QString id, Fsm inputFsm, Fsm outputFsm)
     : id_(id), inputFsm_(inputFsm), outputFsm_(outputFsm)
{

}

QString Link::getId() const
{
     return id_;
}

Fsm Link::getInputFsm() const
{
     return inputFsm_;
}

Fsm Link::getOutputFsm() const
{
     return outputFsm_;
}
