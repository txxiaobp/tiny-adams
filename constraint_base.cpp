#include "constraint_base.h"
#include <QDebug>
#include <cassert>

ConstraintBase::ConstraintBase()
{

}

void ConstraintBase::insertConstraint(Constraint *constraint)
{
    constraintVec.push_back(constraint);
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

std::pair<Matrix, Matrix> ConstraintBase::getTotalJacobianMatrix()
{
    Matrix totalJacobian(getConstraintCount(), 3 * Solid::getGlobalSolidCount());
    Matrix totalGamma(getConstraintCount(), 1);
    int totalRow = 0;

    for (auto *constraint : constraintVec)
    {
        std::vector<int> solidIds = constraint->getSolidIds();
        Matrix jacobianMatrix = constraint->getJacobianMatrix();
        Matrix gammaMatrix = constraint->getGamma();

        for (int row = 0; row < constraint->getFreedomReducedCount(); row++)
        {
            for (int idIndex = 0; idIndex < int(solidIds.size()); idIndex++)
            {
                Solid* solid = Solid::getSolidById(solidIds[idIndex]);
                if (nullptr == solid)
                {
                    assert(nullptr != solid);
                }
                assert(nullptr != solid);
                if (solid->isFix())
                {
                    continue;
                }

                for (int i = 0; i < 3; i++)
                {
                    double jacobianMatrixValue = jacobianMatrix.getValue(row, 3 * idIndex + i);
                    totalJacobian.setValue(totalRow + row, 3 * solidIds[idIndex] + i, jacobianMatrixValue);
                }
            }
            double gammaMatrixValue = gammaMatrix.getValue(row, 0);
            totalGamma.setValue(totalRow + row, 0, gammaMatrixValue);
        }
        totalRow += constraint->getFreedomReducedCount();
    }
    return std::make_pair(totalJacobian, totalGamma);
}
