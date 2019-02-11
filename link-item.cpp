#include "link-item.h"
#include "arrow-item.h"
#include "globals.h"

linkItem::linkItem(QGraphicsItem* parent)
     : commonItem (parent)
{
     number_ = ++linkNumber;

     arrowItem_ = new arrowItem(this);
     nameItem_ = new QGraphicsTextItem(QString::number(number_), this);
     nameItem_->moveBy(standartLenght/2, 0);
     nameItem_->setTextInteractionFlags(Qt::TextEditorInteraction);
}

QString linkItem::getName() const
{
     return QString::number(number_);
}

QRectF linkItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(standartLenght + globals::penWidth, standartWidth + globals::penWidth);
     return QRectF(ptPosition, size);
}

void linkItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
}

void linkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     // Разворачиваем текст, чтобы при развороте всего он остался читаемым
     QTransform textTransform = nameItem_->transform();
     textTransform.rotate(reverseAngle);
     nameItem_->setTransform(textTransform);

     QTransform transform = this->transform();
     transform.rotate(reverseAngle);
     setTransform(transform);
}

linkItem::~linkItem()
{
     number_--;
}

