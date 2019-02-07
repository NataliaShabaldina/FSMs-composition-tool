#include "composition-item.h"
#include "globals.h"

compositionItem::compositionItem()
{

}

QRectF compositionItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(400 + globals::penWidth, 180 + globals::penWidth);
     return QRectF(ptPosition, size);
}

void compositionItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
    painter->save();
    painter->setPen(QPen(Qt::black, globals::penWidth, Qt::DashLine));
    painter->drawRect(0, 0, 400, 180);
    painter->restore();
}
