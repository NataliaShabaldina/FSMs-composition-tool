#include "fsm-item.h"
#include "globals.h"

fsmItem::fsmItem(QGraphicsItem* parent)
     : commonItem(parent)
{
     number_ = ++fsmNumber;

     nameItem_ = new QGraphicsTextItem(QString::number(number_), this);
     nameItem_->moveBy(55, 25);
     nameItem_->setTextInteractionFlags(Qt::TextEditorInteraction);
}

QString fsmItem::getName() const
{
     return nameItem_->toPlainText();
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
    painter->restore();
}



fsmItem::~fsmItem()
{
     fsmNumber--;
}
