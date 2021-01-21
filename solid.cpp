#include "solid.h"
#include <cassert>
#include <cmath>
#include "force.h"
#include <QDebug>
#include <iostream>

int Solid::globalSolidCount = GROUND_ID;
std::unordered_map<int, Solid*> Solid::solidMap;

Solid::Solid(double x, double y, double angle)
    : solidId(globalSolidCount++)
    , isFixed(false)
    , massCenter(0, 0, this)
{
    pointSet.clear();
    pointSet.insert(massCenter);
    Solid::solidMap.insert(std::make_pair(solidId, this));

    posVec[POS_X] = x;
    posVec[POS_Y] = y;
    posVec[POS_ANGLE] = angle;
}

Solid::~Solid()
{
    assert(Solid::solidMap.find(solidId) != Solid::solidMap.end());
    Solid::solidMap.erase(solidId);

    for (auto *force : forceVec)
    {
        if (nullptr == force)
        {
            delete force;
            force = nullptr;
        }
    }
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

Vector Solid::getAccelVec() const
{
    return accelVec;
}

void Solid::setPosVec(Vector posVec)
{
    this->posVec = posVec;
}

void Solid::setVelVec(Vector velVec)
{
    this->velVec = velVec;
}

void Solid::setAccelVec(Vector accelVec)
{
    this->accelVec = accelVec;
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

void Solid::addForce(Vector force, Point point)
{
    forceVec.push_back(new Force(force, point, *this));
}

Vector Solid::toGlobalCordinate(Point &point)
{
    assert(isContainPoint(point));

    Matrix transformMatrix(std::vector<double>{
        cos(posVec[POS_ANGLE]), -sin(posVec[POS_ANGLE]),
        sin(posVec[POS_ANGLE]),  cos(posVec[POS_ANGLE])
    }, 2, 2);

    Vector vec = point - Point(0, 0);
    return transformMatrix * vec + posVec.shrink(0, 2, 0, 1);
}

Vector Solid::getTotalForce() const
{
    Vector retVec;
    for (auto *force : forceVec)
    {
        retVec += force->simplify(massCenter);
    }
    return retVec;
}
