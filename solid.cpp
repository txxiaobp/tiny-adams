#include "solid.h"


int Solid::globalSolidCount = 0;

Solid::Solid()
    : solidId(globalSolidCount++)
{

}

int Solid::getId() const
{
    return solidId;
}

bool Solid::containPoint(Point &point)
{
    if (pointMap.find(point) == pointMap.end())
    {
        return false;
    }
    return true;
}

Point Solid::getMassCenter() const
{
    return massCenter;
}

double Solid::getAngle() const
{
    return angle;
}

double Solid::getAnglarVelocity() const
{
    return angle;
}
