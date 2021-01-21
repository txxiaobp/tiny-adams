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
    , isSetGravity(true)
    , isFixed(false)
    , massCenter(0, 0, *this)  // （0,0）为质心在连体基中的坐标
{
    assert(Solid::solidMap.find(solidId) == Solid::solidMap.end());

    pointSet.insert(massCenter.getPointId());
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

int Solid::getSolidId() const
{
    return solidId;
}

bool Solid::isContainPoint(Point &point)
{
    if (pointSet.find(point.getPointId()) == pointSet.end())
    {
        return false;
    }
    return true;
}

bool Solid::isContainPoint(int pointId)
{
    if (pointSet.find(pointId) == pointSet.end())
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

void Solid::setPosVec(Vector &posVec)
{
    this->posVec = posVec;
}

void Solid::setVelVec(Vector &velVec)
{
    this->velVec = velVec;
}

void Solid::setAccelVec(Vector &accelVec)
{
    this->accelVec = accelVec;
}

void Solid::addPoint(Point &point)
{
    pointSet.insert(point.getPointId());
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

void Solid::addForce(Force &force)
{
    forceSet.insert(force.getForceId());
}

Vector Solid::toGlobalCordinate(Point &point)
{
    assert(isContainPoint(point));

    std::vector<double> matrixVec{
        cos(posVec[POS_ANGLE]), -sin(posVec[POS_ANGLE]),
        sin(posVec[POS_ANGLE]),  cos(posVec[POS_ANGLE])
    };
    Matrix transformMatrix(matrixVec, 2, 2);

    Vector vec = point;
    return transformMatrix * vec + posVec.shrink(0, 2, 0, 1);
}

Vector Solid::getTotalForce() const
{
    Vector retVec;
    for (int forceId : forceSet)
    {
        Force *force = Force::getForceById(forceId);
        assert(nullptr != force);
        retVec += force->simplify(massCenter);
    }

    if (isSetGravity)
    {
        std::vector<double> gravityVec{0, -getMass() * GRAVITY_CONST,  0};
        retVec += gravityVec;
    }
    return retVec;
}

void Solid::setGravity(bool isSetGravity)
{
    this->isSetGravity = isSetGravity;
}

int Solid::getOriginId() const
{
    return massCenter.getPointId();
}
