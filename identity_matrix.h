#ifndef IDENTITYMATRIX_H
#define IDENTITYMATRIX_H

#include "matrix.h"

class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix(int size) : Matrix(size, size) { for (int i = 0; i < size; i++) elem[i][i] = 1.0; }
    virtual ~IdentityMatrix() {}
};

#endif // IDENTITYMATRIX_H
