#include "vector.h"
#include <cassert>

Vector::Vector(std::vector<double> &vec)
    : Matrix(vec, vec.size(), 1)
{
}

Vector::Vector(int vecSize)
    : Matrix(vecSize, 1)
{
}


Vector::~Vector()
{
}

double& Vector::operator[](int index)
{
    assert(index >= 0 && index < row);
    return elem[index][0];
}
