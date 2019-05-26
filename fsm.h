#ifndef FSM_H
#define FSM_H

#include <QString>

/// @brief Класс автомата как логического элемента
class Fsm
{     
private:
     QString name_;
     QString id_;

public:
     Fsm(QString name = "", QString id = "");

     QString getName() const;
     QString getId() const;

     /// @brief Если имя автомата пустое - это внешний относительно композиции автомат(на картинке его нет)
     bool isExternal() const;
};

#endif // FSM_H
