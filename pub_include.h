#ifndef PUB_INCLUDE_H
#define PUB_INCLUDE_H

const int GROUND_ID = -1;
const double GRAVITY_CONST = 9.80665;
const int MATRIX_SINGULAR = -1;
const double DISTANCE_THRESHOLD = 10;

enum
{
    POS_X,
    POS_Y,
    POS_ANGLE
};

enum
{
    FORCE_X,
    FORCE_Y,
    TORQUE_Z
};

#endif // PUB_INCLUDE_H
