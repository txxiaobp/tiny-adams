#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "identity_matrix.h"
#include "matrix.h"
#include "solid.h"
#include <vector>
#include <unordered_map>


typedef enum
{
    REVOLUTE_PAIR
}Constraint_E;


class Constraint;


class ConstraintSet
{
public:
    ConstraintSet();
    ~ConstraintSet();
    void restoreConstraint(Constraint *constraint);

private:
    std::vector<Constraint*> constraintVec;
};

class Constraint
{
public:
    Constraint(Solid &solidA, Point &pointA, Solid &solidB, Point &pointB);
    Constraint(Solid &solidA, int pointAId, Solid &solidB, int pointBId);
    Constraint();
    virtual ~Constraint();
    virtual Matrix getJacobianMatrix() = 0;
    virtual Matrix getGamma() = 0;
    int getId() const;
    int getFreedomReducedCount() const;
    std::vector<int> getSolidIds() const;
    int getConstraintId() const;

    void setSolidA(Solid &solidA);
    void setSolidB(Solid &solidB);
    void setPointA(Point &pointA);
    void setPointB(Point &pointB);

    static std::pair<Matrix, Matrix> getTotalJacobianMatrix();
    static int getTotalFreedomReducedCount();
    static void storeConstraint(Constraint* constraint);

protected:
    int solidAId;
    int solidBId;
    int pointAId;
    int pointBId;

    int constraintId;
    int freedomReducedCount;

    static int globleConstraintCount;
    static std::unordered_map<int, Constraint*> constraintMap;

    static ConstraintSet constraintSet;
};
#endif // CONSTRAINT_H
