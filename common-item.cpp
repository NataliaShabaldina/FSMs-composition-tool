#include "common-item.h"
#include "fsm-item.h"
#include "globals.h"

commonItem::commonItem()
{

}

void commonItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::setOverrideCursor(Qt::PointingHandCursor);
     QGraphicsItem::mousePressEvent(event);
}

void commonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::restoreOverrideCursor();
     QGraphicsItem::mouseReleaseEvent(event);
}
