#include "constraint.h"

#include <cassert>
#include <QDebug>

int Constraint::globleConstraintCount = 0;
std::unordered_map<int, Constraint*> Constraint::constraintMap;

Constraint::Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB)
    : solidA(solidA)
    , solidB(solidB)
    , pointA(pointA)
    , pointB(pointB)
    , constraintId(globleConstraintCount++)
{
    assert(solidA.isContainPoint(pointA));
    assert(solidB.isContainPoint(pointB));

    constraintMap.insert(std::make_pair(constraintId, this));
}

Constraint::~Constraint()
{
    assert(constraintMap.find(constraintId) != constraintMap.end());
    constraintMap.erase(constraintId);
}

int Constraint::getId() const
{
    return constraintId;

}
std::vector<int> Constraint::getSolidIds() const
{
    return std::vector<int>{solidA.getId(), solidB.getId()};
}

int Constraint::getFreedomReducedCount() const
{
    return freedomReducedCount;
}

int Constraint::getTotalFreedomReducedCount()
{
    int totalNum = 0;
    for (auto pair : Constraint::constraintMap)
    {
        totalNum += pair.second->getFreedomReducedCount();
    }
    return totalNum;
}

std::pair<Matrix, Matrix> Constraint::getTotalJacobianMatrix()
{
    Matrix totalJacobian(Constraint::getTotalFreedomReducedCount(), 3 * Solid::getGlobalSolidCount());
    Matrix totalGamma(Constraint::getTotalFreedomReducedCount(), 1);
    int totalRow = 0;

    for (auto pair : Constraint::constraintMap)
    {
        Constraint* constraint = pair.second;
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
