#include "dynamics.h"
#include "solid.h"
#include "constraint.h"
#include "ground.h"
#include "euler_method.h"
#include <cassert>

Dynamics::Dynamics(double timeStep, double timeDuration, Dynamics_E method)
    : timeStep(timeStep)
    , timeDuration(timeDuration)
    , method(method)
{

}

Dynamics::~Dynamics()
{

}

void Dynamics::addSolid(Solid &solid)
{
    solidSet.insert(solid.getSolidId());
}

void Dynamics::addSolid(int solidId)
{
    solidSet.insert(solidId);
}

void Dynamics::calculate()
{
    for (double time = 0; time < timeDuration; time += timeStep)
    {
        auto matrixPair = Constraint::getTotalJacobianMatrix();
        InertialMatrix matrixZ = Solid::getTotalInertialMatrix();
        Vector rhsForce = Solid::getRhsForce();

        Matrix matrixQ = matrixPair.first;
        matrixZ.pushStack(matrixQ.transpose(), DIRECTION_HORIZONTAL);
        matrixQ.pushStack(Matrix(matrixQ.getRow(), matrixQ.getRow()), DIRECTION_HORIZONTAL);
        matrixZ.pushStack(matrixQ, DIRECTION_VERTICAL);

        rhsForce.pushStack(matrixPair.second, DIRECTION_VERTICAL);

        Matrix final = matrixZ / rhsForce;
        Matrix accelMatrix = final.getSubMatrix(0, 3 * Solid::getGlobalSolidCount(), 0, 1);

        EulerMethod eulerMethod;

        eulerMethod.calculateNextTime(accelMatrix, timeStep);

        assert(eulerMethod.isDataReady());

        eulerMethod.setNextTimeVec();
    }
}
