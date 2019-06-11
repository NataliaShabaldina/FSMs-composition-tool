#ifndef SCENE_H
#define SCENE_H

#include "fsm-item.h"
#include "link-item.h"
#include "composition-item.h"

#include <QGraphicsScene>

/// @brief Класс сцены
class Scene : public QGraphicsScene
{
public:
     Scene(QObject* parent = nullptr);
     Scene(const QRectF &sceneRect, QObject *parent = nullptr);

     ///@brief Добавляет на сцену автомат и запоминает в fsms_
     FsmItem* addFsm();

     ///@brief Добавляет на сцену связь и запоминает в links_
     LinkItem* addLink();

     ///@brief Добавляет на сцену композицию и запоминает в compositions_
     CompositionItem* addComposition();
};

#endif // SCENE_H
