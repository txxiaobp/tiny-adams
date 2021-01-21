#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "dynamics_method.h"

class Solid;

class Dynamics
{
public:
    Dynamics(double timeStep, double timeDuration, Dynamics_Method_E method = DYNAMICS_METHOD_RUNGE_KUTTA);
    ~Dynamics();

    void setMethod(Dynamics_Method_E method);
    void calculate();
    Vector calculateSingleStep(Vector &globalPosVec, Vector &globalVelVec);

private:
    double timeStep;
    double timeDuration;
    DynamicsMethod *method;
};

#endif // DYNAMICS_H
