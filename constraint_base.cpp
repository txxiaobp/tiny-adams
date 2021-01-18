#include "constraint_base.h"

ConstraintBase::ConstraintBase(SolidBase &solidBase)
    : solidBase(solidBase)
{

}

int ConstraintBase::getConstraintCount() const
{
    int retNum = 0;
    for (auto *constraint : constraintVec)
    {
        retNum += constraint->getFreedomReducedCount();
    }
    return retNum;
}

Matrix ConstraintBase::getTotalJacobianMatrix()
{
    Matrix retMatrix(getConstraintCount(), 3 * solidBase.getSolidCounts());

    for (auto *constraint : constraintVec)
    {
        std::vector<int> solidIds = constraint->getSolidIds();
        Matrix jacobianMatrix = constraint->getJacobianMatrix();
        Matrix gammaMatrix = constraint->getGamma();
    }
    return retMatrix;
}
