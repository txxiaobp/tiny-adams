#include "solid.h"
#include <cassert>

int Solid::globalSolidCount = GROUND_ID;
std::unordered_map<int, Solid*> Solid::solidMap;

Solid::Solid(double x, double y, double angle)
    : solidId(globalSolidCount++)
    , isFixed(false)
{
    Solid::solidMap.insert(std::make_pair(solidId, this));

    posVec[POS_X] = x;
    posVec[POS_Y] = y;
    posVec[POS_ANGLE] = angle;
}

Solid::~Solid()
{
    assert(Solid::solidMap.find(solidId) != Solid::solidMap.end());
    Solid::solidMap.erase(solidId);
}

int Solid::getId() const
{
    return solidId;
}

bool Solid::isContainPoint(Point &point)
{
    if (pointSet.find(point) == pointSet.end())
    {
        return false;
    }
    return true;
}

Vector Solid::getPosVec() const
{
    return posVec;
}

Vector Solid::getVelVec() const
{
    return velVec;
}

void Solid::setPosVec(Vector posVec)
{
    this->posVec = posVec;
}

void Solid::setVelVec(Vector velVec)
{
    this->velVec = velVec;
}

void Solid::addPoint(Point point)
{
    pointSet.insert(point);
}

int Solid::getGlobalSolidCount()
{
    return globalSolidCount;
}

void Solid::setFix(bool isFixed)
{
    this->isFixed = isFixed;
}

bool Solid::isFix() const
{
    return isFixed;
}

Solid* Solid::getSolidById(int id)
{
    if (Solid::solidMap.find(id) == Solid::solidMap.end())
    {
        return nullptr;
    }
    return Solid::solidMap[id];
}

double Solid::getMass() const
{
    return inertialMatrix.getMass();
}

void Solid::setMass(double mass)
{
    inertialMatrix.setMass(mass);
}

double Solid::getInertial() const
{
    return inertialMatrix.getInertial();
}

void Solid::setInertial(double value)
{
    inertialMatrix.setInertial(value);
}

InertialMatrix Solid::getInertialMatrix() const
{
    return inertialMatrix;
}
