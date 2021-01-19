#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "identity_matrix.h"
#include "matrix.h"
#include "solid.h"
#include <vector>
#include <unordered_map>

class Constraint
{
public:
    Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB);
    virtual ~Constraint();
    virtual Matrix getJacobianMatrix() = 0;
    virtual Matrix getGamma() = 0;
    int getId() const;
    int getFreedomReducedCount() const;
    std::vector<int> getSolidIds() const;

    static std::pair<Matrix, Matrix> getTotalJacobianMatrix();
    static int getTotalFreedomReducedCount();

protected:
    Solid &solidA;
    Solid &solidB;
    Point &pointA;
    Point &pointB;
    int constraintId;
    int freedomReducedCount;

    static int globleConstraintCount;
    static std::unordered_map<int, Constraint*> constraintMap;
};
#endif // CONSTRAINT_H
