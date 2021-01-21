#include "ground.h"

Ground::Ground()
    : Solid()
{
    setGravity(false);
    setMass(INVALID_INERTIAL);
    setInertial(INVALID_INERTIAL);
}
