#include "inertial_matrix.h"
#include <cassert>

InertialMatrix::InertialMatrix()
    : Matrix(3, 3)
{
}

double InertialMatrix::getValue(INERTIAL_E inertialType) const
{
    switch (inertialType)
    {
    case INERTIAL_IXX:
        return elem[0][0];
    case INERTIAL_IYY:
        return elem[1][1];
    case INERTIAL_IZZ:
        return elem[2][2];
    case INERTIAL_IXY:
        return elem[0][1];
    case INERTIAL_IXZ:
        return elem[0][2];
    case INERTIAL_IYZ:
        return elem[1][2];
    default:
        assert(false);
    }
    return -1.0;
}


void InertialMatrix::setValue(INERTIAL_E inertialType, double value)
{
    switch (inertialType)
    {
    case INERTIAL_IXX:
        elem[0][0] = value;
        break;
    case INERTIAL_IYY:
        elem[1][1] = value;
        break;
    case INERTIAL_IZZ:
        elem[2][2] = value;
        break;
    case INERTIAL_IXY:
        elem[0][1] = value;
        break;
    case INERTIAL_IXZ:
        elem[0][2] = value;
        break;
    case INERTIAL_IYZ:
        elem[1][2] = value;
        break;
    default:
        assert(false);
    }
}
