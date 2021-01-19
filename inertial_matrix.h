#ifndef INERTIALMATRIX_H
#define INERTIALMATRIX_H

#include "matrix.h"

const double INVALID_INERTIAL = -1.0;

class InertialMatrix : public Matrix
{
public:
    InertialMatrix();
    ~InertialMatrix() {}

    bool isInertialValid() const;
    double getMass() const;
    void setMass(double value);

    double getInertial() const;
    void setInertial(double value);
};

#endif // INERTIALMATRIX_H
