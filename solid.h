#ifndef SOLID_H
#define SOLID_H

#include <set>
#include <unordered_map>
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
    int getId() const;

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

    void addForce(Vector force, Point point);
    Vector getTotalForce() const;

    Vector toGlobalCordinate(Point &point);
    void addPoint(Point point);
    void setFix(bool isFixed);
    bool isFix() const;

    static int getGlobalSolidCount();
    static Solid* getSolidById(int id);

protected:
    Vector posVec; // 位置向量
    Vector velVec; // 速度向量
    Vector accelVec; // 加速度向量
    int solidId;
    bool isFixed;
    Point massCenter;

    InertialMatrix inertialMatrix;
    std::vector<Force*> forceVec;


    static int globalSolidCount;
    static std::unordered_map<int, Solid*> solidMap;

    std::set<Point> pointSet; // map of point and point id
};

#endif // SOLID_H
