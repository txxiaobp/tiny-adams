#include "dynamics.h"
#include "solid.h"
#include "constraint.h"
#include "ground.h"
#include "euler_method.h"
#include "runge_kutta.h"
#include <cassert>

Dynamics::Dynamics(double timeStep, double timeDuration, Dynamics_Method_E methodE)
    : timeStep(timeStep)
    , timeDuration(timeDuration)
{
    setMethod(methodE);
}

Dynamics::~Dynamics()
{
    if (method)
    {
        delete method;
        method = nullptr;
    }
}

Vector Dynamics::calculateSingleStep()
{
    auto matrixPair = Constraint::getTotalJacobianMatrix();
    InertialMatrix matrixZ = Solid::getTotalInertialMatrix();
    Vector rhsForce = Solid::getRhsForce();

    Matrix matrixQ = matrixPair.first;
    matrixZ.pushStack(matrixQ.transpose(), DIRECTION_HORIZONTAL);
    matrixQ.pushStack(Matrix(matrixQ.getRow(), matrixQ.getRow()), DIRECTION_HORIZONTAL);
    matrixZ.pushStack(matrixQ, DIRECTION_VERTICAL);

    rhsForce.pushStack(matrixPair.second, DIRECTION_VERTICAL);

    Vector final = matrixZ / rhsForce;
    return(final.getSubMatrix(0, 3 * Solid::getGlobalSolidCount(), 0, 1));
}

Vector Dynamics::calculateSingleStep(Vector &globalPosVec, Vector &globalVelVec)
{
    Vector tmpPosVec = Solid::getGlobalPosVec();
    Vector tmpVelVec = Solid::getGlobalVelVec();

    Solid::setGlobalPosVec(globalPosVec);
    Solid::setGlobalVelVec(globalVelVec);

    Vector retVec = calculateSingleStep();

    Solid::setGlobalPosVec(tmpPosVec);
    Solid::setGlobalVelVec(tmpVelVec);

    return retVec;
}

void Dynamics::calculate()
{
    for (double time = 0; time < timeDuration; time += timeStep)
    {
        Vector accelVec = calculateSingleStep();

        assert(nullptr != method);
        method->calculateNextTime(accelVec, timeStep);
        assert(method->isDataReady());
        method->setNextTimeVec();
    }
}

void Dynamics::setMethod(Dynamics_Method_E methodE)
{
    switch (methodE)
    {
    case DYNAMICS_METHOD_EULER:
        method = new EulerMethod(this);
        break;
    case DYNAMICS_METHOD_RUNGE_KUTTA:
        method = new RungeKuttaMethod(this);
        break;
    default:
        assert(false);
    }
}
