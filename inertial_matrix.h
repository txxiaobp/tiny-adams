#ifndef INERTIALMATRIX_H
#define INERTIALMATRIX_H

#include "matrix.h"


class InertialMatrix : public Matrix
{
public:
    InertialMatrix();
    ~InertialMatrix() {}

    double getMass() const;
    void setMass(double value);

    double getInertial() const;
    void setInertial(double value);
};

#endif // INERTIALMATRIX_H
