#include "inertial_matrix.h"
#include <cassert>

InertialMatrix::InertialMatrix()
    : Matrix(3, 3)
{
}

double InertialMatrix::getMass() const
{
    return elem[0][0];
}

void InertialMatrix::setMass(double value)
{
    assert(value > 0);
    elem[0][0] = value;
}

double InertialMatrix::getInertial() const
{
    return elem[2][2];
}

void InertialMatrix::setInertial(double value)
{
    assert(value > 0);
    elem[2][2] = value;
}
