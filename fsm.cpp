#include "fsm.h"

Fsm::Fsm(QString name, QString id)
     : name_(name), id_(id)
{

}

QString Fsm::getName() const
{
     return name_;
}

QString Fsm::getId() const
{
     return id_;
}


