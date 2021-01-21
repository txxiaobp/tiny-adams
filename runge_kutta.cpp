#include "runge_kutta.h"
#include "solid.h"
#include "dynamics.h"


RungeKuttaMethod::RungeKuttaMethod(Dynamics *dynamics)
    : DynamicsMethod(dynamics)
{
}

void RungeKuttaMethod::calculateNextTime(const Vector &accelVec, double timeStep)
{
    nextGlobalVelVec = accelVec * timeStep;
    nextGlobalPosVec = Solid::getGlobalPosVec() + (Solid::getGlobalVelVec() + nextGlobalVelVec) * timeStep / 2;

    Vector k1 = dynamics->calculateSingleStep();

    setDataReady(true);
}
