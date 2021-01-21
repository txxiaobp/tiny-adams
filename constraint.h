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
    Constraint(Solid &solidA, Point &pointA, Solid &solidB, Point &pointB);
    Constraint(Solid &solidA, int pointAId, Solid &solidB, int pointBId);
    virtual ~Constraint();
    virtual Matrix getJacobianMatrix() = 0;
    virtual Matrix getGamma() = 0;
    int getId() const;
    int getFreedomReducedCount() const;
    std::vector<int> getSolidIds() const;
    int getConstraintId() const;

    static std::pair<Matrix, Matrix> getTotalJacobianMatrix();
    static int getTotalFreedomReducedCount();

protected:
    int solidAId;
    int solidBId;
    int pointAId;
    int pointBId;

    int constraintId;
    int freedomReducedCount;

    static int globleConstraintCount;
    static std::unordered_map<int, Constraint*> constraintMap;
};
#endif // CONSTRAINT_H
