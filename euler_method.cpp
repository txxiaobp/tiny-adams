#include "euler_method.h"
#include "solid.h"

EulerMethod::EulerMethod()
{

}

void EulerMethod::calculateNextTime(const Vector &accelVec, double timeStep)
{
    nextGlobalVelVec = accelVec * timeStep;
    nextGlobalPosVec = Solid::getGlobalPosVec() + (Solid::getGlobalVelVec() + nextGlobalVelVec) * timeStep / 2;

    setDataReady(true);
}
