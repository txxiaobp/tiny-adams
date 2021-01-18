#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "identity_matrix.h"
#include "matrix.h"
#include "solid.h"

class Constraint
{
public:
    Constraint(Solid &solidA, Solid &solidB);

protected:
    Solid &solidA;
    Solid &solidB;
};

#endif // CONSTRAINT_H
