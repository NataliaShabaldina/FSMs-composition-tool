#include "view.h"

#include <QKeyEvent>

View::View(QWidget* parent)
     : QGraphicsView (parent)
{

}

View::View(QGraphicsScene* scene, QWidget* parent)
     : QGraphicsView (scene, parent)
{

}

void View::deleteItem()
{
     QGraphicsItem* lastFocused = scene()->focusItem();
     if (lastFocused)
     {
          scene()->removeItem(lastFocused);
     }
}

void View::keyPressEvent(QKeyEvent* event)
{
     /// Удаляем последний выделенный объект
     if (event->key() == Qt::Key_Delete)
     {
          deleteItem();
     }
}
