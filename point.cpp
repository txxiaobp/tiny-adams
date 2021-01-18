#include "point.h"
#include <cassert>

double Point::operator[](int index) const
{
    assert(index >= 0 && index < row);
    return elem[index][0];
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
