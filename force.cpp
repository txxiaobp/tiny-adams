#include "force.h"
#include <cassert>
#include "solid.h"

int Force::forceCount = 0;
std::unordered_map<int, Force*> Force::forceMap;

Force::Force(Vector &forceVec, Point &point, Solid& solid)
    : forceVec(forceVec)
    , point(point)
    , solid(solid)
    , forceId(forceCount++)
{
    // 这里的point是相对于solid上的连体基的位置
    assert(solid.isContainPoint(point));
    assert(forceMap.find(forceId) == forceMap.end());
    forceMap.insert(std::make_pair(forceId, this));
}

Force::~Force()
{
    assert(forceMap.find(forceId) != forceMap.end());
    forceMap.erase(forceId);
}

int Force::getForceId() const
{
    return forceId;
}

Force* Force::getForceById(int id)
{
    assert(Force::forceMap.find(id) != Force::forceMap.end());
    return forceMap[id];
}

// 这里的point也是相对于solid上的连体基的位置，该点需要之前添加到solid中
Vector Force::simplify(Point simplyPoint)
{
    assert(solid.isContainPoint(simplyPoint));

    Vector point1Global = solid.toGlobalCordinate(point);
    Vector point2Global = solid.toGlobalCordinate(simplyPoint);

    Vector pointDis = point1Global - point2Global;

    Vector retForce(forceVec);
    retForce[TORQUE_Z] += pointDis[POS_X] * forceVec[FORCE_Y] - pointDis[POS_Y] * forceVec[FORCE_X];

    return retForce;
}

Vector Force::getForceVec() const
{
    return forceVec;
}

Point Force::getPoint() const
{
    return point;
}


















