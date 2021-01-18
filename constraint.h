#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "identity_matrix.h"
#include "matrix.h"
#include "solid.h"
#include "point.h"

class Constraint
{
public:
    Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB);
    virtual ~Constraint() {}
    virtual Matrix getJacobian();
    virtual Matrix getGamma();
    int getId();


protected:
    Solid &solidA;
    Solid &solidB;
    Point &pointA;
    Point &pointB;
    int id;
    static int globleConstraintCount;
};

int Constraint::globleConstraintCount = 0;

#endif // CONSTRAINT_H
