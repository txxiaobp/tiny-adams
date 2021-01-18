#include "point.h"
#include <cassert>

double Point::operator[](int index) const
{
    assert(index >= 0 && index < row);
    return elem[index][0];
}
