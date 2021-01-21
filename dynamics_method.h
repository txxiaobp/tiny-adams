#ifndef DYNAMICSMETHOD_H
#define DYNAMICSMETHOD_H

#include "matrix.h"

typedef enum
{
    DYNAMICS_METHOD_EULER = 0,
    DYNAMICS_METHOD_RUNGE_KUTTA
}Dynamics_Method_E;

class Dynamics;

class DynamicsMethod
{
public:
    DynamicsMethod(Dynamics *dynamics);
    virtual ~DynamicsMethod() {}
    virtual void calculateNextTime(const Vector &accelVec, double timeStep) = 0;
    void setNextTimeVec();
    bool isDataReady() const;

protected:
    void setDataReady(bool dataReady);

protected:
    Vector nextGlobalPosVec;
    Vector nextGlobalVelVec;
    Dynamics *dynamics;

private:
    bool dataReady;
};

#endif // DYNAMICSMETHOD_H
