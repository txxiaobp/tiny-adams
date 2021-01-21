#include "dynamics_method.h"
#include "solid.h"
#include <cassert>

DynamicsMethod::DynamicsMethod(Dynamics *dynamics)
    : nextGlobalPosVec(Vector(3 * Solid::getGlobalSolidCount(), 1))
    , nextGlobalVelVec(Vector(3 * Solid::getGlobalSolidCount(), 1))
    , dynamics(dynamics)
    , dataReady(false)
{
    assert(nullptr != dynamics);
}

bool DynamicsMethod::isDataReady() const
{
    return dataReady;
}

void DynamicsMethod::setDataReady(bool dataReady)
{
    this->dataReady = dataReady;
}

void DynamicsMethod::setNextTimeVec()
{
    if (!isDataReady())
    {
        return;
    }

    Solid::setGlobalPosVec(nextGlobalPosVec);
    Solid::setGlobalVelVec(nextGlobalVelVec);

    setDataReady(false);
}
