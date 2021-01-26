#include "revolute_pair.h"
#include "identity_matrix.h"
#include <cmath>
#include <cassert>
#include <QDebug>

RevolutePair::RevolutePair(Solid &solidA, Point &pointA, Solid &solidB, Point &pointB)
    : Constraint(solidA, pointA, solidB, pointB)
{
    freedomReducedCount = 2;
}

RevolutePair::RevolutePair(Solid &solidA, int pointAId, Solid &solidB, int pointBId)
    : Constraint(solidA, pointAId, solidB, pointBId)
{
    freedomReducedCount = 2;
}

RevolutePair::RevolutePair()
    : Constraint()
{
    freedomReducedCount = 2;
}

Matrix RevolutePair::getJacobianMatrix()
{
    int matrixRow = 2;
    int matrixCol = 6;

    Solid *solidA = Solid::getSolidById(solidAId);
    Solid *solidB = Solid::getSolidById(solidBId);
    Point *pointA = Point::getPointById(pointAId);
    Point *pointB = Point::getPointById(pointBId);

    assert(nullptr != solidA);
    assert(nullptr != solidB);
    assert(nullptr != pointA);
    assert(nullptr != pointB);

    double thetaA = solidA->getPosVec()[POS_ANGLE];
    double thetaB = solidB->getPosVec()[POS_ANGLE];

    std::vector<double> matrixVec{
        1.0, 0.0, -sin(thetaA) * (*pointA)[0] - cos(thetaA) * (*pointA)[1], -1.0,  0.0,  sin(thetaB) * (*pointB)[0] + cos(thetaB) * (*pointB)[1],
        0.0, 1.0,  cos(thetaA) * (*pointA)[0] - sin(thetaA) * (*pointA)[1],  0.0, -1.0, -cos(thetaB) * (*pointB)[0] + sin(thetaB) * (*pointB)[1],
    };
    Matrix jacobianMatrix(matrixVec, matrixRow, matrixCol);

    return jacobianMatrix;
}

Matrix RevolutePair::getGamma()
{
    int matrixRow = 2;
    int matrixCol = 1;

    Solid *solidA = Solid::getSolidById(solidAId);
    Solid *solidB = Solid::getSolidById(solidBId);
    Point *pointA = Point::getPointById(pointAId);
    Point *pointB = Point::getPointById(pointBId);

    assert(nullptr != solidA);
    assert(nullptr != solidB);
    assert(nullptr != pointA);
    assert(nullptr != pointB);

    double thetaA = solidA->getPosVec()[POS_ANGLE];
    double thetaB = solidB->getPosVec()[POS_ANGLE];

    double thetaAVelocity = solidA->getVelVec()[POS_ANGLE];
    double thetaBVelocity = solidB->getVelVec()[POS_ANGLE];

    std::vector<double> matrixVec{
        (cos(thetaA) * (*pointA)[0] - sin(thetaA) * (*pointA)[1]) * pow(thetaAVelocity, 2)
      - (cos(thetaB) * (*pointB)[0] - sin(thetaB) * (*pointB)[1]) * pow(thetaBVelocity, 2),

        (sin(thetaA) * (*pointA)[0] + cos(thetaA) * (*pointA)[1]) * pow(thetaAVelocity, 2)
      - (sin(thetaB) * (*pointB)[0] + cos(thetaB) * (*pointB)[1]) * pow(thetaBVelocity, 2),
    };
    Matrix jacobianMatrix(matrixVec, matrixRow, matrixCol);

    return jacobianMatrix;
}

RevolutePair* RevolutePair::createRevolute()
{
    RevolutePair* revolutePair = new RevolutePair();
    Constraint::storeConstraint(revolutePair);
    return revolutePair;
}
