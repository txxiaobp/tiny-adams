#include "mainwindow.h"
#include "matrix.h"

#include "link.h"
#include "constraint.h"
#include "revolute_pair.h"
#include "point.h"
#include "dynamics.h"


#include <QApplication>
#include <QDebug>
#include <iostream>

Link ground;

int main(int argc, char *argv[])
{

//    double length = 2;
//    double angle = 0;

//    Link link(length * cos(angle), length * sin(angle), angle);
//    link.setMass(10);
//    link.setInertial(3);

//    Point *groundOrigin = Point::getPointById(ground.getOriginId());
//    Point point(-length, 0, link);

//    link.addPoint(point);

//    std::vector<double> vec{0, 0, 0};
//    Vector linkVec(vec);
//    link.setVelVec(linkVec);

//    RevolutePair revolutePair(ground, *groundOrigin, link, point);

//    double timeStep = 0.05;
//    double timeDuration = 1;

//    Dynamics dynamics(timeStep, timeDuration);
//    dynamics.calculate();


//    return 0;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}
