#include "mainwindow.h"
#include "matrix.h"

#include "point.h"
#include "link.h"
#include "constraint.h"
#include "constraint_base.h"
#include "revolute_pair.h"
#include "ground.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    ConstraintBase constraintBase;

//    Link link1(0, 1, M_PI / 2);
//    Link link2(1, 1, -M_PI / 4);

//    Point point1(1, 0);
//    Point point2(-1, 0);

    Ground ground;


    ground.setFix(true);
    double length = 2;
    double angle = M_PI / 6;
    Link link1(length * cos(angle), length * sin(angle), angle);

    Point point1(0, 0);
    Point point2(-length, 0);

    ground.addPoint(point1);
    link1.addPoint(point2);

    std::vector<double> vec{0, 1, 6};
    link1.setVelVec(Vector(vec));

    constraintBase.insertConstraint(new RevolutePair(ground, link1, point1, point2));
    auto matrixPair = constraintBase.getTotalJacobianMatrix();
    matrixPair.first.showMatrix();
    matrixPair.second.showMatrix();



//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
