#include "vector.h"

Vector::Vector(std::vector<double> &vec)
    : Matrix(vec, vec.size(), 1)
{
}


Vector::~Vector()
{
}
