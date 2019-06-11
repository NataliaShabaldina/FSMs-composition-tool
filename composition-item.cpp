#include "composition-item.h"
#include "fsm-item.h"
#include "link-item.h"
#include "globals.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif //QT_DEBUG

CompositionItem::CompositionItem(QGraphicsItem* parent)
     : CommonItem(parent)
{

}

void CompositionItem::formComposition()
{
     fsmVector fsms;
     linkVector links;

     auto getFsmsAndLinks = [&fsms, &links](QList<QGraphicsItem*> allItems)
     {
          for( const auto& item : allItems )
          {
               if( globals::customTypes::fsm == item->type() )
               {
                    // Автомат уже сформирован
                    fsms.push_back( dynamic_cast<FsmItem*>(item)->getFsm() );
               }
               else if ( globals::customTypes::link == item->type() )
               {
                    // Связь нужно сначала сформировать
                    LinkItem* link = dynamic_cast<LinkItem*>(item);
                    link->formLink();
                    links.push_back( link->getLink() );
               }
          }
     };

     getFsmsAndLinks(collidingItems());

     composition_ = Composition(fsms, links);
}

Composition CompositionItem::getComposition() const
{
     return composition_;
}


void CompositionItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
     QMenu menu;
     QAction* removeAction = menu.addAction(QIcon(":/context/icons/delete.svg"), "&Delete");
     removeAction->setShortcut(QKeySequence::Delete);
     QAction* formAction = menu.addAction("&Form");
     QAction* currAct = menu.exec(event->screenPos());
     if (currAct == removeAction)
     {
          removeItem();
     }
     else if (currAct == formAction)
     {
          formComposition();
          composition_.formXmlFile();
#ifdef QT_DEBUG
          printFsmsAndLinks();
#endif
     }
}

#ifdef QT_DEBUG
void CompositionItem::printFsmsAndLinks()
{
     for(const auto& fsm : composition_.getFsms())
     {
          qDebug() << "FSM: " << fsm.getId();
     }
     for(const auto& link : composition_.getLinks())
     {
          qDebug() << "Link: " << link.getId() << "\n Input FSM: " << link.getInputFsm().getId() << "   Output FSM: " << link.getOutputFsm().getId();
     }


     fsmVector myFSMs = composition_.getFsms();
     if (myFSMs.size() != 2)
     {
          qDebug() << "we need 2 components...";
          return;
     }

     //int countFSMs = myFSMs.size();
     QString name1 = myFSMs[0].getId() + ".aut";
     QString name2 = myFSMs[1].getId() + ".aut";

     linkVector myLinks = composition_.getLinks();
     size_t countLinks = myLinks.size();



     QString channels1_inp = "", channels1_out = "", channels2_inp = "", channels2_out = "", ext_channel1 = "", ext_channel2 = "";
     int E_number=0;
     for (size_t i = 0; i < countLinks; i++)
     {
          if (myLinks[i].getInputFsm().getId() == myFSMs[0].getId())
          {
               channels1_inp += myLinks[i].getId();
               channels1_inp += '|';
               if (myLinks[i].getOutputFsm().getId()=="")
               {
                    ext_channel2 += "E" + QString::number(E_number)+',';
               }
               E_number++;
          }

          if (myLinks[i].getOutputFsm().getId() == myFSMs[0].getId())
          {
               channels1_out += myLinks[i].getId();
               channels1_out += '|';
               if (myLinks[i].getInputFsm().getId()=="")
               {
                    ext_channel2 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }

          if (myLinks[i].getInputFsm().getId() == myFSMs[1].getId())
          {
               channels2_inp += myLinks[i].getId();
               channels2_inp += '|';
               if (myLinks[i].getOutputFsm().getId()=="")
               {
                    ext_channel1 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }

          if (myLinks[i].getOutputFsm().getId() == myFSMs[1].getId())
          {
               channels2_out += myLinks[i].getId();
               channels2_out += '|';
               if (myLinks[i].getInputFsm().getId()=="")
               {
                    ext_channel1 += "E" + QString::number(E_number) + ',';
               }
               E_number++;
          }
     }

     channels1_out.remove(channels1_out.size() - 1, 1);
     channels2_out.remove(channels2_out.size() - 1, 1);
     ext_channel1.remove(ext_channel1.size() - 1, 1);
     ext_channel2.remove(ext_channel2.size() - 1, 1);

     QString chan_inp = channels1_inp+ext_channel1;
     QString chan_out = channels1_out+ext_channel2;

     QString command1 = "read_para_fsm " +channels1_inp+channels1_out+" "+name1+" poly"+name1;
     QString command2 = "read_para_fsm " + channels2_inp + channels2_out + " " + name2 + " poly" + name2;
     QString command3 = "chan_sync " + channels1_inp + channels1_out+ "|E "+ channels2_inp + channels2_out+ "|E "+ " poly" + name1 + " poly" + name2 + " sync" + name1 + " sync" + name2;
     QString command4 = "expansion " + ext_channel1 +","+ ext_channel2 + name2 + " exp" + name2;
     QString command5 = "product poly" + name1 + " exp" + name2 +" pro" + ".aut";
     QString command6 = "restriction " + ext_channel1 + "," + ext_channel2 + " pro"+".aut" + " restr"+ ".aut";
     QString command7 = "support " + chan_inp + ","+ chan_out + "," + "E" + "("+ QString::number(E_number) +")" + " restr" + ".aut" + " supp"+ ".aut";
     QString command8 = "write_para_fsm " + channels1_inp + channels1_out + "|E " + "ext_channel1" + "|" + "ext_channel2" + " supp" + ".aut" + " fsm" + ".aut";

     qDebug() << command1 << "\n" << command2 << "\n" << command3 << "\n" << command4 << "\n" << command5 << "\n" << command6 << "\n"<< command7 << "\n"<< command8 << "\n";

}
#endif //QT_DEBUG

int CompositionItem::type() const
{
     return globals::customTypes::composition;
}

QRectF CompositionItem::boundingRect() const
{
     QPointF ptPosition(0 - globals::penWidth, 0 - globals::penWidth);
     QSizeF size(400 + globals::penWidth, 180 + globals::penWidth);
     return { ptPosition, size };
}

void CompositionItem::paint(QPainter* painter,
                            const QStyleOptionGraphicsItem*,
                            QWidget*)
{
     painter->save();
     painter->setPen(QPen(Qt::black, globals::penWidth, Qt::DashLine));
     painter->drawRect(0, 0, 400, 180);
     painter->restore();
}
