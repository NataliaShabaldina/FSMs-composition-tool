#include "link-item.h"

linkItem::linkItem()
{
     number_ = ++linkNumber;
}

QRectF linkItem::boundingRect() const
{
     QPointF ptPosition(0 - penWidth, -10 - penWidth);
     QSizeF size(80 + penWidth, 20 + penWidth);
     return QRectF(ptPosition, size);
}

void linkItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
    painter->save();
    painter->setPen(QPen(Qt::black, penWidth));
    painter->drawLine(0, 0, 80, 0);
    painter->drawLine(80, 0, 70, 10);
    painter->drawLine(80, 0, 70, -10);
    painter->drawText(35, -5, QString::number(number_));
    painter->restore();
}

void linkItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::setOverrideCursor(Qt::PointingHandCursor);
     QGraphicsItem::mousePressEvent(event);
}

void linkItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
     QApplication::restoreOverrideCursor();
     QGraphicsItem::mouseReleaseEvent(event);
}
