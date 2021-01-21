#ifndef POINT_H
#define POINT_H

#include "matrix.h"
#include "pub_include.h"
#include <unordered_map>

class Solid;

class Point
{
public:
    Point(double x, double y, Solid& solid);
    Point();  // 认为依附于地面
    ~Point();
    double& operator[](int index);
    double operator[](int index) const;
    bool operator<(const Point &point) const;
    Vector operator-(const Point &anotherPoint);

    int getPointId() const;
    int getDimension() const;

    static Point* getPointById(int id);

private:
    Matrix data;
    int solidId; //点依附的实体，若依附于ground，则是空间中固定不变的点
    int pointId;
    static int pointCount;
    static std::unordered_map<int, Point*> pointMap;
};

#endif // POINT_H
