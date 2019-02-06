#include "fsm-item.h"
#include "globals.h"

fsmItem::fsmItem()
{
     number_ = ++fsmNumber;
}

QRectF fsmItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(120 + globals::penWidth, 80 + globals::penWidth);
     return QRectF(ptPosition, size);
}

void fsmItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
    painter->save();
    painter->setPen(QPen(Qt::black, globals::penWidth));
    painter->drawRect(0, 0, 120, 80);
    painter->drawText(55, 35, QString::number(number_));
    painter->restore();
}

void fsmItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::setOverrideCursor(Qt::PointingHandCursor);
     QGraphicsItem::mousePressEvent(event);
}

void fsmItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::restoreOverrideCursor();
     QGraphicsItem::mouseReleaseEvent(event);
}