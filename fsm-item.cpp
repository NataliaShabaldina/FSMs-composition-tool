#include "fsm-item.h"
#include "globals.h"

#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

FsmItem::FsmItem(QGraphicsItem* parent)
     : CommonItem(parent)
{
     number_ = ++fsmNumber;

     nameItem_ = new QGraphicsTextItem(QString::number(number_), this);
     nameItem_->moveBy(55, 25);
     nameItem_->setTextInteractionFlags(Qt::TextEditorInteraction);

     file_.setFileName("");
}

QString FsmItem::getName() const
{
     return nameItem_->toPlainText();
}

Fsm FsmItem::getFsm() const
{
     return fsm_;
}

void FsmItem::formFsm()
{
     fsm_ = Fsm( getName(), getName().left(4) );
}

int FsmItem::type() const
{
     return globals::customTypes::fsm;
}

QRectF FsmItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(120 + globals::penWidth + globals::collideError, 80 + globals::penWidth + globals::collideError);
     return { ptPosition, size };
}

void FsmItem::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget*)
{
     painter->save();
     painter->setPen(QPen(Qt::black, globals::penWidth));
     painter->drawRect(0, 0, 120, 80);
     painter->restore();
}

void FsmItem::onAttachFile()
{
     QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                 "Choose the .aut file",
                                                 "",
                                                 "*.aut");
     if (!filePath.isEmpty())
     {
          file_.setFileName(filePath);
          file_.open(QIODevice::ReadOnly);
          if (!file_.isOpen())
          {
               QMessageBox::critical(nullptr, "File opening problems", "Can't open the file");
               file_.setFileName("");
               return;
          }
     }

     auto getFileName = [](const QFile& file)
     {
          QFileInfo fileInfo(file.fileName());
          return fileInfo.fileName();
     };

     file_.copy( getFileName(file_) );
}

void FsmItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
     QMenu menu;
     QAction* removeAction = menu.addAction("&Delete");
     removeAction->setIcon(QIcon(":/context/icons/delete.svg"));
     QAction* attachFile = menu.addAction("&Attach file");
     attachFile->setIcon(QIcon(":/context/icons/file.svg"));
     QAction* currAct = menu.exec(event->screenPos());
     if (currAct == removeAction)
     {
          removeItem();
     }
     else if (currAct == attachFile)
     {
          onAttachFile();
     }
}

FsmItem::~FsmItem()
{
     fsmNumber--;
}
