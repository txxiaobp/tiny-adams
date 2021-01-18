#ifndef CONSTRAINTBASE_H
#define CONSTRAINTBASE_H

#include "constraint.h"
#include "matrix.h"
#include "solid.h"
#include <vector>

class ConstraintBase
{
public:
    ConstraintBase();

    int getConstraintCount() const;
    void insertConstraint(Constraint *constraint);
    std::pair<Matrix, Matrix> getTotalJacobianMatrix();

private:
    std::vector<Constraint*> constraintVec;
};

#endif // CONSTRAINTBASE_H
