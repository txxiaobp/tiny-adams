#include "mainwindow.h"
#include "matrix.h"

#include "link.h"
#include "constraint.h"
#include "revolute_pair.h"
#include "point.h"
#include "dynamics.h"
#include "ground.h"

#include <QApplication>
#include <QDebug>
#include <iostream>


int main(int argc, char *argv[])
{
    Ground ground;

    double length = 2;
    double angle = 0;

    Link link1(length * cos(angle), length * sin(angle), angle);
    link1.setMass(10);
    link1.setInertial(3);

    Point &groundOrigin = *Point::getPointById(ground.getOriginId());
    Point point2(-length, 0, link1);

    link1.addPoint(point2);

    std::vector<double> vec{0, 0, 0};
    Vector linkVec(vec);
    link1.setVelVec(linkVec);

    RevolutePair revolutePair(ground, groundOrigin, link1, point2);
    //auto matrixPair = Constraint::getTotalJacobianMatrix();



//    InertialMatrix matrixZ = link1.getInertialMatrix();


//    Matrix matrixQ = matrixPair.first;
//    matrixZ.pushStack(matrixQ.transpose(), DIRECTION_HORIZONTAL);

//    matrixQ.pushStack(Matrix(matrixQ.getRow(), matrixQ.getRow()), DIRECTION_HORIZONTAL);

//    matrixZ.pushStack(matrixQ, DIRECTION_VERTICAL);


//    Vector linkForce = link1.getTotalForce();

//    linkForce.pushStack(matrixPair.second, DIRECTION_VERTICAL);

//    Matrix final = matrixZ / linkForce;



//    qDebug() << "Mass Matrix";
//    matrixZ.showMatrix();

//    qDebug() << "Force Matrix";
//    linkForce.showMatrix();


//    qDebug() << "Result Matrix";
//    final.showMatrix();

    double timeStep = 0.05;
    double timeDuration = 1;


    Dynamics dynamics(timeStep, timeDuration);
    //dynamics.addSolid(ground);
    dynamics.addSolid(link1);
    dynamics.calculate();


    return 0;


//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
