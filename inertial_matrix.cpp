#include "inertial_matrix.h"
#include <cassert>

InertialMatrix::InertialMatrix(int row)
    : Matrix(row, row)
{
    for (int r = 0; r < row; r++)
    {
        elem[r][r] = INVALID_INERTIAL;
    }
}

double InertialMatrix::getMass() const
{
    return elem[0][0];
}

void InertialMatrix::setMass(double value)
{
    elem[0][0] = elem[1][1] = value;
}

double InertialMatrix::getInertial() const
{
    return elem[2][2];
}

void InertialMatrix::setInertial(double value)
{
    elem[2][2] = value;
}

bool InertialMatrix::isInertialValid() const
{
    return getMass() != INVALID_INERTIAL && getInertial() != INVALID_INERTIAL;
}
