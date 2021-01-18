#ifndef SOLID_H
#define SOLID_H

#include <map>
#include "point.h"

class Solid
{
public:
    Solid();
    virtual ~Solid() {}

    bool containPoint(Point &point);
    Point getMassCenter() const;
    double getAngle() const;
    double getAnglarVelocity() const;
    int getId() const;

protected:
    Point massCenter;
    double angle;
    int solidId;

    static int globalSolidCount;

    std::map<Point, int> pointMap; // map of point and point id
};

#endif // SOLID_H
