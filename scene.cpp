#include "scene.h"
#include "globals.h"
#include "fsm.h"
#include "link.h"
#include "composition.h"

#include <vector>
#include <QDebug>


using fsmVector = std::vector<Fsm>;
using linkVector = std::vector<Link>;
using compositionVector = std::vector<Composition>;

Scene::Scene(QObject* parent)
     : QGraphicsScene(parent)
{
}

Scene::Scene(const QRectF &sceneRect, QObject *parent)
     : QGraphicsScene(sceneRect, parent)
{
}

void Scene::addFsm()
{
     auto fsm = new FsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(fsm);
     fsms_.push_back(fsm);
}

void Scene::addLink()
{
     auto link = new LinkItem;
     link->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(link);
     links_.push_back(link);
}

void Scene::addComposition()
{
     auto compostion = new CompositionItem;
     compostion->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     compostion->setZValue(globals::behindAllItems);
     addItem(compostion);
     compositions_.push_back(compostion);
}
