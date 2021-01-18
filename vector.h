#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"
#include <vector>

class Vector : public Matrix
{
public:
    Vector(std::vector<double> &vec);
    Vector(int vecSize);
    virtual ~Vector();
};

#endif // VECTOR_H
