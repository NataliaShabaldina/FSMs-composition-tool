#include "scene.h"
#include "globals.h"

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
     auto fsm = new fsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(fsm);
     fsms_.push_back(fsm);
}

void Scene::addLink()
{
     auto link = new linkItem;
     link->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(link);
     links_.push_back(link);
}

void Scene::addComposition()
{
     auto compostion = new compositionItem;
     compostion->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     compostion->setZValue(globals::behindAllItems);
     addItem(compostion);
     compositions_.push_back(compostion);
}
