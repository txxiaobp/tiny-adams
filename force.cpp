#include "force.h"
#include <cassert>

Force::Force(Vector forceVec, Point point, Solid& solid)
    : forceVec(forceVec)
    , point(point)
    , solid(solid)
{
    // 这里的point是相对于solid上的连体基的位置
    assert(solid.isContainPoint(point));
}

// 这里的point也是相对于solid上的连体基的位置，该点需要之前添加到solid中
Vector Force::simplify(Point& simplyPoint)
{
    assert(solid.isContainPoint(simplyPoint));

    Vector point1Global = solid.toGlobalCordinate(point);
    Vector point2Global = solid.toGlobalCordinate(simplyPoint);

    Vector pointDis = point1Global - point2Global;

    Vector retForce(forceVec);
    retForce[TORQUE_Z] += pointDis[POS_X] * forceVec[FORCE_Y] - pointDis[POS_Y] * forceVec[FORCE_X];

    return retForce;
}


















