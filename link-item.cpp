#include "link-item.h"
#include "arrow-item.h"
#include "globals.h"

#include <QAction>
#include <QMenu>

linkItem::linkItem(QGraphicsItem* parent)
     : commonItem (parent)
{
     number_ = ++linkNumber;

     arrowItem_ = new arrowItem(this);
     nameItem_ = new QGraphicsTextItem(QString::number(number_), this);
     nameItem_->moveBy(standartLenght/2, 0);
     nameItem_->setTextInteractionFlags(Qt::TextEditorInteraction);
     nameItem_->setFlag(GraphicsItemFlag::ItemIgnoresTransformations);

}

QString linkItem::getName() const
{
     return nameItem_->toPlainText();
}

void linkItem::rotate()
{
     QTransform transform = this->transform();
     transform.rotate(reverseAngle);
     setTransform(transform);
}

QRectF linkItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(standartLenght + globals::penWidth, standartWidth + globals::penWidth);
     return { ptPosition, size };
}

void linkItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
}

void linkItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
     QMenu menu;
     QAction* removeAction = menu.addAction("&Delete");
     removeAction->setIcon(QIcon(":/context/icons/delete.svg"));
     QAction* rotateAction = menu.addAction("&Rotate");
     rotateAction->setIcon(QIcon(":/context/icons/rotate.svg"));
     QAction* currAct = menu.exec(event->screenPos());
     if (currAct == removeAction)
     {
          removeItem();
     }
     else if (currAct == rotateAction)
     {
          rotate();
     }
}

void linkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     rotate();
}

linkItem::~linkItem()
{
     linkNumber--;
}

