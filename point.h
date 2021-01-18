#ifndef POINT_H
#define POINT_H

#include "vector.h"

class Point : public Vector
{
public:
    Point(int dimension = 2) : Vector(dimension) {}
    ~Point();
};

#endif // POINT_H