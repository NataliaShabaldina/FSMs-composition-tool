#ifndef FSM_H
#define FSM_H

#include <QString>

/// @brief Класс автомата как логического элемента
class Fsm
{     
private:
     QString name_;
     QString fullPath_;
     QString fileName_;

public:
     Fsm(const QString& name = "", const QString& fullPath = "", const QString& fileName = "");

     QString getName() const;
     QString getFullPath() const;
     QString getFileName() const;

     /// @brief Если имя автомата пустое - это внешний относительно композиции автомат(на картинке его нет)
     bool isExternal() const;
};

#endif // FSM_H
