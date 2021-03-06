#ifndef EULERMETHOD_H
#define EULERMETHOD_H

#include "dynamics_method.h"

class Dynamics;

class EulerMethod : public DynamicsMethod
{
public:
    EulerMethod(Dynamics *dynamics);
    virtual ~EulerMethod() {}

    void calculateNextTime(const Vector &accelVec, double timeStep);

private:

};

#endif // EULERMETHOD_H
