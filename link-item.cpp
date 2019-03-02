#include "link-item.h"
#include "arrow-item.h"
#include "globals.h"

#include <QAction>
#include <QMenu>

#include <QDebug>

LinkItem::LinkItem(QGraphicsItem* parent)
     : CommonItem (parent)
{
     number_ = ++linkNumber;

     arrowItem_ = new ArrowItem(this);
     nameItem_ = new QGraphicsTextItem(QString::number(number_), this);
     nameItem_->moveBy(standartLenght/2, 0);
     nameItem_->setTextInteractionFlags(Qt::TextEditorInteraction);
     nameItem_->setFlag(GraphicsItemFlag::ItemIgnoresTransformations);
}

QString LinkItem::getName() const
{
     return nameItem_->toPlainText();
}

void LinkItem::rotate()
{
     setTransformOriginPoint(41, 10);
     QTransform transform = this->transform();

     qDebug() << transformOriginPoint().x() << "and " << transformOriginPoint().y();
     transform.rotate(reverseAngle);
     setTransform(transform);
}

QRectF LinkItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(standartLenght + globals::penWidth + globals::collideError, standartWidth + globals::penWidth + globals::collideError);
     return { ptPosition, size };
}

void LinkItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
}

void LinkItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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

void LinkItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     qDebug() << event->pos().x() << " and " << event->pos().y() << endl;

     qDebug() << collidingItems().size();
}

void LinkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     rotate();
}

LinkItem::~LinkItem()
{
     linkNumber--;
}

