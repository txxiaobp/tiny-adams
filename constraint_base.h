#ifndef CONSTRAINTBASE_H
#define CONSTRAINTBASE_H

#include "constraint.h"
#include "matrix.h"
#include "solid_base.h"
#include <vector>

class ConstraintBase
{
public:
    ConstraintBase(SolidBase &solidBase);

    int getConstraintCount() const;

private:
    Matrix getTotalJacobianMatrix();

private:
    std::vector<Constraint*> constraintVec;
    SolidBase &solidBase;
};

#endif // CONSTRAINTBASE_H
