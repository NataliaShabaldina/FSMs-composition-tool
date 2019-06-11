#include "link-item.h"
#include "arrow-item.h"
#include "globals.h"
#include "fsm-item.h"

#include <QAction>
#include <QMenu>
#include <QMessageBox>

#include <QDebug>

LinkItem::LinkItem(QGraphicsItem* parent)
     : CommonItem (parent)
{
     number_ = linkNumber++;

     arrowItem_ = new ArrowItem(this);
     idItem_ = new QGraphicsTextItem(QString::number(number_), this);
     idItem_->moveBy(standartLenght/2, 0);
     idItem_->setTextInteractionFlags(Qt::TextEditorInteraction);
     idItem_->setFlag(GraphicsItemFlag::ItemIgnoresTransformations);
     idItem_->setFlag(GraphicsItemFlag::ItemIsMovable);

     startPoint_ = QPointF(0, standartWidth/2);
     endPoint_ = QPointF(standartLenght + globals::penWidth, standartWidth/2);
}

QString LinkItem::getId() const
{
     return idItem_->toPlainText();
}

Link LinkItem::getLink() const
{
     return link_;
}

void LinkItem::formLink()
{
     auto containsPoint = [this](const FsmItem& fsm, const QPointF& pointOfLink)
     {
          return fsm.contains(fsm.mapFromItem(this, pointOfLink));
     };

     auto removeNotFsms = [](QList<QGraphicsItem*> allItems)
     {
          QList<FsmItem*> fsmItems;
          for( const auto& item : allItems )
          {
               if ( globals::customTypes::fsm == item->type())
               {

                    FsmItem* fsm = dynamic_cast<FsmItem*>(item);
                    fsm->formFsm();
                    fsmItems.append(fsm);
               }
          }
          return fsmItems;
     };

     auto form = [&containsPoint, &removeNotFsms, this]()
     {
          QList<FsmItem*> collidingFsms = removeNotFsms(this->collidingItems());
          Fsm inputFsm = Fsm();
          Fsm outputFsm = Fsm();
          for( const auto& fsm : collidingFsms )
          {
               if( containsPoint(fsm, startPoint_) )
               {
                    outputFsm = fsm->getFsm();
               }
               else if ( containsPoint(fsm, endPoint_ ) )
               {
                    inputFsm = fsm->getFsm();
               }
          }

          if(inputFsm.isExternal() && outputFsm.isExternal())
          {
               QMessageBox::warning(nullptr, "Link problem", "One of the links doest't connect any FSM");
          }

          return Link(getId(), inputFsm, outputFsm);
     };

     link_ = form();
}

#ifdef QT_DEBUG
void LinkItem::printDebugInfo()
{
     formLink();
     qDebug() << link_.getId();
     qDebug() << "input: " << link_.getInputFsm().getId();
     qDebug() << "output: " << link_.getOutputFsm().getId();

}
#endif //QT_DEBUG

int LinkItem::type() const
{
     return globals::customTypes::link;
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
     Q_UNUSED(painter);
}

void LinkItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
     QMenu menu;
#ifdef QT_DEBUG
     QAction* formAction = menu.addAction("&Form");
#endif //QT_DEBUG
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
#ifdef QT_DEBUG
     else if (currAct == formAction)
     {
          printDebugInfo();
     }
#endif //QT_DEBUG
}

#ifdef QT_DEBUG
void LinkItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     qDebug() << event->pos().x() << " and " << event->pos().y() << endl;

     qDebug() << collidingItems().size();
}
#endif //QT_DEBUG

void LinkItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     rotate();
     QGraphicsItem::mouseDoubleClickEvent(event);
}

LinkItem::~LinkItem()
{
     linkNumber--;
}

