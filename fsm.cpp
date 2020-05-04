#include "fsm.h"

Fsm::Fsm(const QString& name, const QString& fullPath, const QString& fileName)
     : name_(name), fullPath_(fullPath), fileName_(fileName)
{

}

QString Fsm::getName() const
{
     return name_;
}

QString Fsm::getFullPath() const
{
     return fullPath_;
}

QString Fsm::getFileName() const
{
    return fileName_;
}

bool Fsm::isExternal() const
{
     return name_.isEmpty();
}
