#ifndef PUB_INCLUDE_H
#define PUB_INCLUDE_H

#include <QColor>

const int INVALID_ID = -1;
const int GROUND_ID = 0;
const double GRAVITY_CONST = 9.80665;
const int MATRIX_SINGULAR = -1;
const double DISTANCE_THRESHOLD = 10;

const QColor DEFAULT_COLOR = Qt::black;
const Qt::PenStyle DEFAULT_STYLE = Qt::SolidLine;
const int DEFAULT_WIDTH = 4;
const int DEFAULT_CHOSEN_WIDTH = 7;
const double EPS = 1e-8;
const double CIRCLE_MARGIN_RATIO = 0.1;  // 圆中心线超出圆周的长度占半径的比例

typedef enum
{
    SHAPE_LINE = 0,
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,

    SOLID_LINK,

    OBJECT_MAX,
}Object_E;

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
