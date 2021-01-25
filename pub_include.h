#ifndef PUB_INCLUDE_H
#define PUB_INCLUDE_H

#include <QColor>

const int GROUND_ID = -1;
const double GRAVITY_CONST = 9.80665;
const int MATRIX_SINGULAR = -1;
const double DISTANCE_THRESHOLD = 10;

const QColor DEFAULT_COLOR = Qt::black;
const Qt::PenStyle DEFAULT_STYLE = Qt::SolidLine;
const int DEFAULT_WIDTH = 4;
const int DEFAULT_CHOSEN_WIDTH = 7;

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