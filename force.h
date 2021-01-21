#ifndef FORCE_H
#define FORCE_H


#include "point.h"
#include <unordered_map>

class Solid;

class Force
{
public:
    Force(Vector &forceVec, Point &point, Solid& solid);
    virtual ~Force();

    Vector getForceVec() const;
    Point getPoint() const;
    int getForceId() const;

    Vector simplify(Point point);
    static Force* getForceById(int id);

protected:
    Vector forceVec;
    Point point;
    Solid& solid;
    int forceId;

    static int forceCount;
    static std::unordered_map<int, Force*> forceMap;
};

#endif // FORCE_H
