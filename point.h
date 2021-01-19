#ifndef POINT_H
#define POINT_H

#include "matrix.h"
#include "pub_include.h"

class Point
{
public:
    Point(double x = 0, double y = 0);
    double& operator[](int index);
    bool operator<(const Point &point) const;
    Vector operator-(const Point &anotherPoint);

private:
    Matrix data;
};

#endif // POINT_H
