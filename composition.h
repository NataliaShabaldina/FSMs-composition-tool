#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "fsm.h"
#include "link.h"

#include <vector>

class Composition
{
public:
     Composition();

private:
     std::vector<Fsm> fsms_;
     std::vector<Link> links_;
};

#endif // COMPOSITION_H
