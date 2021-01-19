#ifndef FORCE_H
#define FORCE_H

#include "solid.h"
#include "point.h"

class Force
{
public:
    Force(Vector forceVec, Point point, Solid& solid);
    virtual ~Force() {}

    Vector simplify(Point& point);

protected:
    Vector forceVec;
    Point point;
    Solid& solid;
};

#endif // FORCE_H
