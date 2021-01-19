#ifndef SOLID_H
#define SOLID_H

#include <set>
#include <unordered_map>
#include "inertial_matrix.h"

const int GROUND_ID = -1;

enum
{
    POS_X,
    POS_Y,
    POS_ANGLE
};

enum
{
    FORCE_X,
    FORCE_Y,
    TORQUE_Z
};

class Solid
{
public:
    Solid(double x = 0, double y = 0, double angle = 0);
    virtual ~Solid();

    bool isContainPoint(Vector &point);
    int getId() const;

    void setPosVec(Vector posVec);
    void setVelVec(Vector velVec);

    Vector getPosVec() const;
    Vector getVelVec() const;

    double getMass() const;
    void setMass(double mass);

    double getInertial() const;
    void setInertial(double value);

    InertialMatrix getInertialMatrix() const;

    void addForce(Vector force, Vector point);

    Point toGlobalCordinate(Point &point);
    void addPoint(Vector point);
    void setFix(bool isFixed);
    bool isFix() const;

    static int getGlobalSolidCount();
    static Solid* getSolidById(int id);

protected:
    Vector posVec; // 位置向量
    Vector velVec; // 速度向量
    int solidId;
    bool isFixed;

    InertialMatrix inertialMatrix;
    std::vector<Vector> forceVec;

    static int globalSolidCount;
    static std::unordered_map<int, Solid*> solidMap;

    std::set<Vector> pointSet; // map of point and point id
};

#endif // SOLID_H
