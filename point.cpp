#include "point.h"
#include <cassert>


Point::Point(double x, double y)
    : data(2, 1)
{
    data[POS_X] = x;
    data[POS_Y] = x;
}

double& Point::operator[](int index)
{
    assert(index >= 0 && index < data.getRow());
    return data[index];
}

bool Point::operator<(const Point &point) const
{
    return data < point.data;
}

Vector Point::operator-(const Point &anotherPoint)
{
    Vector retVec(2, 1);
    retVec[POS_X] = data[POS_X] - anotherPoint.data[POS_X];
    retVec[POS_Y] = data[POS_Y] - anotherPoint.data[POS_Y];
    return retVec;
}
