#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "fsm.h"
#include "link.h"
#include "globals.h"

#include <QFile>

#include <vector>

/// @brief Композиция как логический элемент
///        Композиция является основным элементом
///        Содержит в себе связи и автоматы
///        Связи и автоматы извне композиции никак не обрабатываются
class Composition
{
private:
     fsmVector fsms_;
     linkVector links_;

public:
     Composition(fsmVector fsms = fsmVector(), linkVector links = linkVector());

     void formXmlFile() const;

     fsmVector getFsms() const;
     linkVector getLinks() const;
};

#endif // COMPOSITION_H
