#ifndef DYNAMICSMETHOD_H
#define DYNAMICSMETHOD_H

#include "matrix.h"

class DynamicsMethod
{
public:
    DynamicsMethod();
    virtual ~DynamicsMethod() {}
    virtual void calculateNextTime(const Vector &accelVec, double timeStep) = 0;
    void setNextTimeVec();
    bool isDataReady() const;

protected:
    void setDataReady(bool dataReady);

protected:
    Vector nextGlobalPosVec;
    Vector nextGlobalVelVec;

private:
    bool dataReady;
};

#endif // DYNAMICSMETHOD_H
