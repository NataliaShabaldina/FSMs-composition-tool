#ifndef GLOBALS_H
#define GLOBALS_H

#include <QGraphicsItem>

namespace globals
{
     enum { penWidth = 2 };
     enum { behindAllItems = -1 };
     enum { collideError = 2 };
     enum customTypes { fsm = QGraphicsItem::UserType + 1, link, composition };
}

#endif // GLOBALS_H
