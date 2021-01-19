#include "mainwindow.h"
#include "matrix.h"

#include "link.h"
#include "constraint.h"
#include "revolute_pair.h"
#include "ground.h"
#include "point.h"

#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
//    Link link1(0, 1, M_PI / 2);
//    Link link2(1, 1, -M_PI / 4);

//    Point point1(1, 0);
//    Point point2(-1, 0);

    Ground ground;


    ground.setFix(true);
    double length = 2;
    double angle = M_PI / 6;

    Link link1(length * cos(angle), length * sin(angle), angle);
    link1.setMass(2);
    link1.setInertial(3);

    Point point1(0, 0);
    Point point2(-length, 0);

    ground.addPoint(point1);
    link1.addPoint(point2);

    std::vector<double> vec{0, 1, 6};
    link1.setVelVec(Vector(vec));

    RevolutePair revolutePair(ground, link1, point1, point2);
    auto matrixPair = Constraint::getTotalJacobianMatrix();
    //matrixPair.first.showMatrix();
    //matrixPair.second.showMatrix();

    InertialMatrix matrixZ = link1.getInertialMatrix();
    matrixZ.showMatrix();
    std::cout << std::endl << std::endl;
    Matrix matrixQ = matrixPair.first;
    matrixZ.pushStack(matrixQ.transpose(), DIRECTION_HORIZONTAL);
    matrixZ.showMatrix();

    std::cout << std::endl << std::endl;

    matrixQ.pushStack(Matrix(matrixQ.getRow(), matrixQ.getRow()), DIRECTION_HORIZONTAL);
    matrixQ.showMatrix();

    std::cout << std::endl << std::endl;

    matrixZ.pushStack(matrixQ, DIRECTION_VERTICAL);
    matrixZ.showMatrix();



    return 0;


//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
