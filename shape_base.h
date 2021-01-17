#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QObject>
#include <vector>
#include <deque>
#include "shape.h"

const int SHAPE_STACK_SIZE = 50;

class ShapeBase
{
public:
    ShapeBase();
    ~ShapeBase();
    void push(Shape *shape);
    void pop();
    bool isEmpty();

    std::vector<Shape*> getShapes();

private:
    std::map<int, Shape*> shapeMap;
    std::deque<int> shapeStack;
    int shapeId;
};

#endif // SHAPEBASE_H
