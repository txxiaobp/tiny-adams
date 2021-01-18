#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "identity_matrix.h"
#include "matrix.h"
#include "solid.h"
#include "point.h"
#include <vector>

class Constraint
{
public:
    Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB);
    virtual ~Constraint() {}
    virtual Matrix getJacobianMatrix() = 0;
    virtual Matrix getGamma() = 0;
    int getId() const;
    int getFreedomReducedCount() const;
    std::vector<int> getSolidIds() const;

protected:
    Solid &solidA;
    Solid &solidB;
    Point &pointA;
    Point &pointB;
    int constraintId;
    int freedomReducedCount;
    static int globleConstraintCount;
};
#endif // CONSTRAINT_H
