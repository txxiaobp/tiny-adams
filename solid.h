#ifndef SOLID_H
#define SOLID_H

#include <set>
#include <unordered_map>
#include <unordered_set>
#include "inertial_matrix.h"
#include "pub_include.h"
#include "point.h"

class Force;
class Point;

class Solid
{
public:
    Solid(double x = 0, double y = 0, double angle = 0);
    virtual ~Solid();

    bool isContainPoint(Point &point);
    bool isContainPoint(int pointId);
    int getSolidId() const;

    void setPosVec(Vector posVec);
    void setVelVec(Vector velVec);
    void setAccelVec(Vector accelVec);

    Vector getPosVec() const;
    Vector getVelVec() const;
    Vector getAccelVec() const;

    double getMass() const;
    void setMass(double mass);

    double getInertial() const;
    void setInertial(double value);

    InertialMatrix getInertialMatrix() const;

    void addForce(Force &force);
    Vector getTotalForce() const;

    void setGravity(bool isSetGravity);

    Vector toGlobalCordinate(Point &point);
    void addPoint(Point &point);
    void setFix(bool isFixed);
    bool isFix() const;
    int getOriginId() const;

    static int getGlobalSolidCount();
    static Solid* getSolidById(int id);

protected:
    Vector posVec; // 位置向量
    Vector velVec; // 速度向量
    Vector accelVec; // 加速度向量

    int solidId;
    bool isSetGravity;
    bool isFixed;
    Point massCenter;

    InertialMatrix inertialMatrix;

    std::unordered_set<int> constraintSet;
    std::unordered_set<int> forceSet;
    std::unordered_set<int> pointSet; // map of point and point id


    static int globalSolidCount;
    static std::unordered_map<int, Solid*> solidMap;
};

#endif // SOLID_H
