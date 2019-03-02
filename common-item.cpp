#include "common-item.h"
#include "fsm-item.h"
#include "globals.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

CommonItem::CommonItem(QGraphicsItem* parent)
     : QGraphicsItem(parent)
{

}

void CommonItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::setOverrideCursor(Qt::PointingHandCursor);
     setFocus();
     QGraphicsItem::mousePressEvent(event);
}

void CommonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::restoreOverrideCursor();
     QGraphicsItem::mouseReleaseEvent(event);
}

void CommonItem::keyPressEvent(QKeyEvent* event)
{
     /// Удаляем последний выделенный объект
     if (event->key() == Qt::Key_Delete)
     {
          scene()->removeItem(this);
     }
}

void CommonItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
     QMenu menu;
     QAction* removeAction = menu.addAction(QIcon(":/context/icons/delete.svg"), "&Delete");
     removeAction->setShortcut(QKeySequence::Delete);
     QAction* currAct = menu.exec(event->screenPos());
     if (currAct == removeAction)
     {
          removeItem();
     }
}


void CommonItem::removeItem()
{
     scene()->removeItem(this);
}
