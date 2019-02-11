#include "view.h"

#include <QKeyEvent>

View::View(QWidget* parent)
     : QGraphicsView (parent)
{

}

View::View(QGraphicsScene* scene, QWidget* parent)
     : QGraphicsView (scene, parent)
{

}


