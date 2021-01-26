#ifndef SENSOR_H
#define SENSOR_H

#include <unordered_map>
#include "matrix.h"

class Solid;

class Sensor
{
public:
    Sensor();
    void subscribe(const Vector &vector); //从外界获取信息
    void publish(const Vector &vector);   //将信息传送到其他物体

private:
    std::unordered_map<int, void(*)(const Vector&)> publishers;
};

#endif // SENSOR_H
