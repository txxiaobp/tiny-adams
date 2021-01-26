#include "sensor.h"
#include "solid.h"



Sensor::Sensor()
{
}


void Sensor::subscribe(const Vector &vector)
{
    publish(vector);
}


void Sensor::publish(const Vector &vector)
{
    for (auto pair : publishers)
    {
        pair.second(vector);
    }
}
