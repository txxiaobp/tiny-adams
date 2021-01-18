#include "revolute_pair.h"
#include "identity_matrix.h"
#include <cmath>

RevolutePair::RevolutePair(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB)
    : Constraint(solidA, solidB, pointA, pointB)
{

}

Matrix RevolutePair::getJacobian()
{
    int matrixRow = 2;
    int matrixCol = 6;
    double thetaA = solidA.getAngle();
    double thetaB = solidB.getAngle();

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

    double thetaA = solidA.getAngle();
    double thetaB = solidB.getAngle();

    double thetaAVelocity = solidA.getAnglarVelocity();
    double thetaBVelocity = solidB.getAnglarVelocity();

    Matrix jacobianMatrix(std::vector<double>{
        (cos(thetaA) * pointA[0] - sin(thetaA) * pointA[1]) * pow(thetaAVelocity, 2)
      - (cos(thetaB) * pointB[0] - sin(thetaB) * pointB[1]) * pow(thetaBVelocity, 2),

        (sin(thetaA) * pointA[0] + cos(thetaA) * pointA[1]) * pow(thetaAVelocity, 2)
      - (sin(thetaB) * pointB[0] + cos(thetaB) * pointB[1]) * pow(thetaBVelocity, 2),
    }, matrixRow, matrixCol);

    return jacobianMatrix;
}
