#include "composition.h"

Composition::Composition(fsmVector fsms, linkVector links)
     : fsms_(std::move(fsms)), links_(std::move(links))
{

}

fsmVector Composition::getFsms() const
{
     return fsms_;
}

linkVector Composition::getLinks() const
{
     return links_;
}
