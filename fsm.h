#ifndef FSM_H
#define FSM_H

#include <QString>

class Fsm
{     
public:
     Fsm(QString name = "", QString id = "");

     QString getName() const;
     QString getId() const;

private:
     QString name_;
     QString id_;
};

#endif // FSM_H
