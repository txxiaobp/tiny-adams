#ifndef INERTIALMATRIX_H
#define INERTIALMATRIX_H

#include "matrix.h"

typedef enum
{
    INERTIAL_IXX = 0,
    INERTIAL_IYY,
    INERTIAL_IZZ,
    INERTIAL_IXY,
    INERTIAL_IXZ,
    INERTIAL_IYZ,
    INERTIAL_MAX
}INERTIAL_E;

class InertialMatrix : public Matrix
{
public:
    InertialMatrix();
    ~InertialMatrix();

    double getValue(INERTIAL_E inertialType) const;
    void setValue(INERTIAL_E inertialType, double value);
};

#endif // INERTIALMATRIX_H
