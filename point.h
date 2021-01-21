#ifndef POINT_H
#define POINT_H

#include "matrix.h"
#include "pub_include.h"

class Solid;

class Point
{
public:
    Point(double x = 0, double y = 0, Solid *solid = nullptr); //solid为nullptr时，认为该点依附于地面
    double& operator[](int index);
    bool operator<(const Point &point) const;
    Vector operator-(const Point &anotherPoint);

private:
    Matrix data;
    Solid *solid; //点依附的实体，若依附于ground，则是空间中固定不变的点
};

#endif // POINT_H
