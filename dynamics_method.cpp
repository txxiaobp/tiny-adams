#include "dynamics_method.h"
#include "solid.h"

DynamicsMethod::DynamicsMethod()
    : dataReady(false)
    , nextGlobalPosVec(Vector(3 * Solid::getGlobalSolidCount(), 1))
    , nextGlobalVelVec(Vector(3 * Solid::getGlobalSolidCount(), 1))
{
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
