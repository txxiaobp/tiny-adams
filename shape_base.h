#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QObject>
#include <vector>
#include "shape.h"

class ShapeBase
{
public:
    ShapeBase();
    ~ShapeBase();
    void push(Shape *shape);
    std::vector<Shape*> getShapes();

private:
    std::map<int, Shape*> shapeMap;
    int shapeId;
};

#endif // SHAPEBASE_H
