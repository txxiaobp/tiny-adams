#ifndef FORCE_H
#define FORCE_H

#include "solid.h"

class Force
{
public:
    Force(Vector forceVec, Vector point, Solid& solid);
    virtual ~Force() {}

    Vector simplify(Vector& point);

protected:
    Vector forceVec;
    Vector point;
    Solid& solid;
};

#endif // FORCE_H
