#include "point.h"
#include <cassert>

Point::Point(double x, double y)
    : Vector(2)
{
    elem[0][0] = x;
    elem[1][0] = y;
}

bool Point::operator<(const Point &point) const
{
    if (row < point.row)
    {
        return true;
    }
    else if (row > point.row)
    {
        return false;
    }

    for (int r = 0; r < row; r++)
    {
        if (elem[r][0] < point.elem[r][0])
        {
            return true;
        }
        else if (elem[r][0] > point.elem[r][0])
        {
            return false;
        }
    }
    return false;
}
