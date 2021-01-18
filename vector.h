#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"
#include <vector>

enum
{
    POS_X = 0,
    POS_Y,
    POS_ANGLE,
};

class Vector : public Matrix
{
public:
    Vector(std::vector<double> &vec);
    Vector(int vecSize = 3);
    virtual ~Vector();
    double& operator[](int index);
};

#endif // VECTOR_H
