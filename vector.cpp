#include "vector.h"

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
