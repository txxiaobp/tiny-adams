#include "revolute_pair.h"
#include "identity_matrix.h"
#include <cmath>
#include <QDebug>

RevolutePair::RevolutePair(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB)
    : Constraint(solidA, solidB, pointA, pointB)
{
    freedomReducedCount = 2;
}

Matrix RevolutePair::getJacobianMatrix()
{
    int matrixRow = 2;
    int matrixCol = 6;
    double thetaA = solidA.getPosVec()[POS_ANGLE];
    double thetaB = solidB.getPosVec()[POS_ANGLE];

    Matrix jacobianMatrix(std::vector<double>{
        1.0, 0.0, -sin(thetaA) * pointA[0] - cos(thetaA) * pointA[1], -1.0,  0.0,  sin(thetaB) * pointB[0] + cos(thetaB) * pointB[1],
        0.0, 1.0,  cos(thetaA) * pointA[0] - sin(thetaA) * pointA[1],  0.0, -1.0, -cos(thetaB) * pointB[0] + sin(thetaB) * pointB[1],
    }, matrixRow, matrixCol);

    return jacobianMatrix;
}

Matrix RevolutePair::getGamma()
{
    int matrixRow = 2;
    int matrixCol = 1;

    double thetaA = solidA.getPosVec()[POS_ANGLE];
    double thetaB = solidB.getPosVec()[POS_ANGLE];

    double thetaAVelocity = solidA.getVelVec()[POS_ANGLE];
    double thetaBVelocity = solidB.getVelVec()[POS_ANGLE];

    Matrix jacobianMatrix(std::vector<double>{
        (cos(thetaA) * pointA[0] - sin(thetaA) * pointA[1]) * pow(thetaAVelocity, 2)
      - (cos(thetaB) * pointB[0] - sin(thetaB) * pointB[1]) * pow(thetaBVelocity, 2),

        (sin(thetaA) * pointA[0] + cos(thetaA) * pointA[1]) * pow(thetaAVelocity, 2)
      - (sin(thetaB) * pointB[0] + cos(thetaB) * pointB[1]) * pow(thetaBVelocity, 2),
    }, matrixRow, matrixCol);

    return jacobianMatrix;
}
