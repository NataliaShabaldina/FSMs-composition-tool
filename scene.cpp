#include "scene.h"
#include "globals.h"
#include "fsm.h"
#include "link.h"
#include "composition.h"

#include <vector>
#include <QDebug>

Scene::Scene(QObject* parent)
     : QGraphicsScene(parent)
{
}

Scene::Scene(const QRectF &sceneRect, QObject *parent)
     : QGraphicsScene(sceneRect, parent)
{
}

FsmItem* Scene::addFsm()
{
     auto fsm = new FsmItem;
     fsm->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(fsm);
     return fsm;
}

LinkItem* Scene::addLink()
{
     auto link = new LinkItem;
     link->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     addItem(link);
     return link;
}

CompositionItem* Scene::addComposition()
{
     auto compostion = new CompositionItem;
     compostion->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
     compostion->setZValue(globals::behindAllItems);
     addItem(compostion);
     return compostion;
}


