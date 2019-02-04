#include "fsm-item.h"

fsmItem::fsmItem()
{
     fsmNumber++;
}

QRectF fsmItem::boundingRect() const
{
     QPointF ptPosition(0 - penWidth, 0 - penWidth);
     QSizeF size(120 + penWidth, 80 + penWidth);
     return QRectF(ptPosition, size);
}

void fsmItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
    painter->save();
    painter->setPen(QPen(Qt::black, penWidth));
    painter->drawRect(0, 0, 120, 80);
    painter->drawText(55, 35, QString::number(fsmNumber));
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
