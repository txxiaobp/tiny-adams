#ifndef RUNGEKUTTAMETHOD_H
#define RUNGEKUTTAMETHOD_H

#include "dynamics_method.h"

class Dynamics;

class RungeKuttaMethod : public DynamicsMethod
{
public:
    RungeKuttaMethod(Dynamics *dynamics);
    virtual ~RungeKuttaMethod() {}

    void calculateNextTime(const Vector &accelVec, double timeStep);

private:

};

#endif // RUNGEKUTTAMETHOD_H
