#include "point.h"
#include <cassert>
#include <QDebug>
#include "solid.h"

int Point::pointCount = 0;
std::unordered_map<int, Point*> Point::pointMap;


Point::Point(double x, double y, Solid &solid)
    : data(2, 1)
    , solidId(solid.getSolidId())
    , pointId(pointCount++)
{
    assert(Point::pointMap.find(pointId) == Point::pointMap.end());
    Point::pointMap.insert(std::make_pair(pointId, this));
    data[POS_X] = x;
    data[POS_Y] = y;
}

Point::Point()
    : data(2, 1)
    , solidId(GROUND_ID)
    , pointId(pointCount++)
{
    assert(Point::pointMap.find(pointId) == Point::pointMap.end());
    Point::pointMap.insert(std::make_pair(pointId, this));
    data[POS_X] = 0;
    data[POS_Y] = 0;
}

Point::~Point()
{
    assert(Point::pointMap.find(pointId) != Point::pointMap.end());
    Point::pointMap.erase(pointId);
}

double& Point::operator[](int index)
{
    assert(index >= 0 && index < data.getRow());
    return data[index];
}

double Point::operator[](int index) const
{
    assert(index >= 0 && index < data.getRow());
    return data[index];
}

bool Point::operator<(const Point &point) const
{
    return data < point.data;
}

Vector Point::operator-(const Point &anotherPoint)
{
    Vector retVec(2, 1);
    retVec[POS_X] = data[POS_X] - anotherPoint.data[POS_X];
    retVec[POS_Y] = data[POS_Y] - anotherPoint.data[POS_Y];
    return retVec;
}

int Point::getPointId() const
{
    return pointId;
}

Point* Point::getPointById(int id)
{
    assert(Point::pointMap.find(id) != Point::pointMap.end());
    return pointMap[id];
}

int Point::getDimension() const
{
    return 3;
}
