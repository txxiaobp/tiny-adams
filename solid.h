#ifndef SOLID_H
#define SOLID_H

#include <set>
#include <unordered_map>
#include "point.h"
#include "vector.h"

const int GROUND_ID = -1;

class Solid
{
public:
    Solid(double x = 0, double y = 0, double angle = 0);
    virtual ~Solid();

    bool isContainPoint(Point &point);
    int getId() const;

    void setPosVec(Vector posVec);
    void setVelVec(Vector velVec);

    Vector getPosVec() const;
    Vector getVelVec() const;

    void addPoint(Point point);
    void setFix(bool isFixed);
    bool isFix() const;

    static int getGlobalSolidCount();
    static Solid* getSolidById(int id);

protected:
    Vector posVec; // 位置向量
    Vector velVec; // 速度向量
    int solidId;
    bool isFixed;

    static int globalSolidCount;
    static std::unordered_map<int, Solid*> solidMap;

    std::set<Point> pointSet; // map of point and point id
};

#endif // SOLID_H
