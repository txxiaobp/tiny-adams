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
    shapeMap.insert(std::make_pair(shapeId++, shape));
}
