#ifndef REVOLUTEPAIR_H
#define REVOLUTEPAIR_H

#include "constraint.h"
#include "matrix.h"

class RevolutePair : public Constraint
{
public:
    RevolutePair(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB);
    ~RevolutePair() {}
    virtual Matrix getJacobianMatrix();
    virtual Matrix getGamma();
};

#endif // REVOLUTEPAIR_H
