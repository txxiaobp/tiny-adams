#ifndef REVOLUTEPAIR_H
#define REVOLUTEPAIR_H

#include "constraint.h"
#include "matrix.h"

class RevolutePair : public Constraint
{
public:
    RevolutePair(Solid &solidA, Point &pointA, Solid &solidB, Point &pointB);
    RevolutePair(Solid &solidA, int pointAId, Solid &solidB, int pointBId);
    ~RevolutePair() {}
    virtual Matrix getJacobianMatrix();
    virtual Matrix getGamma();
};

#endif // REVOLUTEPAIR_H
