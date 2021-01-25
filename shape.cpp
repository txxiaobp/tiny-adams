#include "shape.h"
#include "pub_include.h"
#include <cassert>
#include <QDebug>
#include <map>


std::unordered_map<int, Shape*> Shape::shapeMap;
int Shape::globalShapeCount = 0;


Shape::Shape(QColor shapeColor, int shapeType, int shapeChosenType)
    : isChosen(false)
    , ready(false)
    , shapeColor(shapeColor)
    , shapeType(shapeType)
    , shapeChosenType(shapeChosenType)
    , shapeId(globalShapeCount++)
{
    assert(shapeMap.find(shapeId) == shapeMap.end());
    shapeMap.insert(std::make_pair(shapeId, this));
}

Shape::~Shape()
{
    assert(shapeMap.find(shapeId) != shapeMap.end());
    shapeMap.erase(shapeId);
}


Shape* Shape::getNearestShape(QPoint& mousePoint)
{
    std::map<double, Shape*> map;
    for (auto shapeMapPair : shapeMap)
    {
        double distance = shapeMapPair.second->calDistance(mousePoint);

        if (distance <= DISTANCE_THRESHOLD)
        {
            map.insert(std::make_pair(distance, shapeMapPair.second));
        }
        else
        {
            shapeMapPair.second->setChosen(false);
        }
    }

    if (map.empty())
    {
        return nullptr;
    }
    return map.begin()->second;
}

void Shape::captureNearestShape(QPoint& mousePoint)
{
    Shape *shape = Shape::getNearestShape(mousePoint);
    if (nullptr != shape)
    {
        shape->setChosen(true);
    }
}

int Shape::getShapeId() const
{
    return shapeId;
}

void Shape::setChosen(bool isChosen)
{
    this->isChosen = isChosen;
}
