#ifndef FORCE_H
#define FORCE_H


#include "point.h"

class Solid;

class Force
{
public:
    Force(Vector forceVec, Point point, Solid& solid);
    virtual ~Force() {}

    Vector getForceVec() const;
    Point getPoint() const;

    Vector simplify(Point point);

protected:
    Vector forceVec;
    Point point;
    Solid& solid;
};

#endif // FORCE_H
