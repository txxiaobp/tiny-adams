#include "ground.h"
#include <cassert>

Ground::Ground()
{
    assert(solidId == GROUND_ID);
    setFix(true);
}
