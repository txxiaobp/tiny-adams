#include "sensor.h"
#include "solid.h"
#include "matrix.h"


Sensor::Sensor()
{

}


void Sensor::subscribe(const Vector &vector)
{
    publish(vector);
}


void Sensor::publish()
{
    for (auto pair : publishers)
    {
        pair.second(vector);
    }
}
