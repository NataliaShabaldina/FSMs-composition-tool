#ifndef GLOBALS_H
#define GLOBALS_H

#include <QGraphicsItem>

class Fsm;
class FsmItem;
class Link;
class LinkItem;
class Composition;
class CompositionItem;

using fsmItemsVector = std::vector<FsmItem*>;
using linkItemsVector = std::vector<LinkItem*>;
using compositionItemsVector = std::vector<CompositionItem*>;
using fsmVector = std::vector<Fsm>;
using linkVector = std::vector<Link>;
using compositionVector = std::vector<Composition>;

namespace globals
{
     enum { penWidth = 2 };
     enum { behindAllItems = -1 };
     // Добавляем для более точного определения коллизий
     enum { collideError = 2 };
     enum customTypes { fsm = QGraphicsItem::UserType + 1, link, composition };
}

#endif // GLOBALS_H
