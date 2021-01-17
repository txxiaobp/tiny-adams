#include "shape_base.h"

ShapeBase::ShapeBase()
    : shapeId(0)
{

}

ShapeBase::~ShapeBase()
{
    for (auto shapePair: shapeMap)
    {
        if (shapePair.second)
        {
            delete shapePair.second;
            shapePair.second = nullptr;
        }
    }
    shapeId = 0;
}

std::vector<Shape*> ShapeBase::getShapes()
{
    std::vector<Shape*> shapes;
    for (auto shapePair: shapeMap)
    {
        shapes.push_back(shapePair.second);
    }
    return shapes;
}

void ShapeBase::push(Shape *shape)
{
    if (shapeStack.size() >= SHAPE_STACK_SIZE)
    {
        shapeStack.pop_front();
    }

    shapeStack.push_back(shapeId);
    shapeMap.insert(std::make_pair(shapeId, shape));
    shapeId++;
}

void ShapeBase::pop()
{
    if (isEmpty())
    {
        return;
    }
    int lastShapeId = shapeStack.back();
    shapeStack.pop_back();
    if (shapeMap.find(lastShapeId) == shapeMap.end())
    {
        return;
    }
    shapeMap.erase(lastShapeId);
}

bool ShapeBase::isEmpty()
{
    return shapeStack.empty();
}
