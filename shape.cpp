#include "shape.h"
#include "solid.h"
#include "pub_include.h"
#include <cassert>
#include <QDebug>
#include <map>
#include <QPainter>


std::unordered_map<int, Shape*> Shape::shapeMap;
std::unordered_set<Shape*> Shape::chosenShapeSet;
int Shape::globalShapeCount = 0;
Shape* Shape::currentCapturedShape = nullptr;

Shape::Shape(int solidId, QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : isChosen(false)
    , isCaptured(false)
    , ready(false)
    , shapeColor(shapeColor)
    , shapeStyle(shapeStyle)
    , shapeWidth(shapeWidth)
    , shapeChosenWidth(shapeChosenWidth)
    , shapeId(globalShapeCount++)
    , solidId(solidId)
    , currentCapturedPoint(nullptr)
{
    assert(shapeMap.find(shapeId) == shapeMap.end());
    shapeMap.insert(std::make_pair(shapeId, this));
}

Shape::Shape(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : isChosen(false)
    , isCaptured(false)
    , ready(false)
    , shapeColor(shapeColor)
    , shapeStyle(shapeStyle)
    , shapeWidth(shapeWidth)
    , shapeChosenWidth(shapeChosenWidth)
    , shapeId(globalShapeCount++)
    , solidId(INVALID_ID)
    , currentCapturedPoint(nullptr)
{
    assert(Shape::shapeMap.find(shapeId) == Shape::shapeMap.end());
    Shape::shapeMap.insert(std::make_pair(shapeId, this));
}

Shape::~Shape()
{
    assert(Shape::shapeMap.find(shapeId) != Shape::shapeMap.end());
    Shape::shapeMap.erase(shapeId);

//    if (Shape::chosenShapeSet.find(this) != Shape::chosenShapeSet.end())
//    {
//        Shape::chosenShapeSet.erase(this);
//    }
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
            shapeMapPair.second->setCaptured(false);
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
        shape->setCaptured(true);
        shape->capturePoint(mousePoint);
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

void Shape::setCaptured(bool isCaptured)
{
    this->isCaptured = isCaptured;
    if (isCaptured)
    {
        Shape::currentCapturedShape = this;
    }
    else
    {
        Shape::currentCapturedShape = nullptr;
        currentCapturedPoint = nullptr;
    }
}

bool Shape::isChosenOrCaptured() const
{
    return isChosen || isCaptured;
}

int Shape::getSolidId() const
{
    return solidId;
}

void Shape::chooseShape(QPoint& mousePoint, bool isMultiple)
{
    Shape::captureNearestShape(mousePoint);

    /* 如果不是多选，清空已选Set */
    if (!isMultiple)
    {
        Shape::clearChosenSet();
    }

    /* 如果是多选，继续添加 */
    if (currentCapturedShape)
    {
        Solid *solid = Solid::getSolidById(currentCapturedShape->getSolidId());
        if (nullptr != solid)
        {
            solid->setChosen(true);
        }
        else
        {
            Shape::pushChosenSet(currentCapturedShape);
        }
    }
    else
    {
        Shape::clearChosenSet();
    }
}

void Shape::pushChosenSet(Shape *shape)
{
    assert(shape);
    shape->setChosen(true);
    chosenShapeSet.insert(shape);
}

void Shape::clearChosenSet()
{
    for (Shape *shape : chosenShapeSet)
    {
        shape->setChosen(false);
    }
    chosenShapeSet.clear();
}

void Shape::setPainter(QPainter *qPainter)
{
    if (isChosenOrCaptured())
    {
        QPen pen(shapeColor, shapeChosenWidth);
        pen.setStyle(shapeStyle);
        qPainter->setPen(pen);//设置画笔形式
    }
    else
    {
        QPen pen(shapeColor, shapeWidth);
        pen.setStyle(shapeStyle);
        qPainter->setPen(pen);//设置画笔形式
    }
}

void Shape::setPointPainter(QPainter *qPainter)
{
    QPen pen(Qt::red, 2);
    pen.setStyle(Qt::SolidLine);
    qPainter->setPen(pen);//设置画笔形式
}

void Shape::deleteShapes()
{
    for (Shape *shape : Shape::chosenShapeSet)
    {
        if (nullptr != shape)
        {
            delete shape;
            shape = nullptr;
        }
    }
    Shape::chosenShapeSet.clear();
}

std::vector<Shape*> Shape::getShapes()
{
    std::vector<Shape*> shapeVec;
    for (auto shapeMapPair : shapeMap)
    {
        shapeVec.push_back(shapeMapPair.second);
    }
    return shapeVec;
}

void Shape::showPoint(QPoint &point, QPainter *qPainter)
{
    const int pointRecSideLength = 4;

    setPointPainter(qPainter);
    qPainter->drawRect(point.x() - pointRecSideLength,
                       point.y() - pointRecSideLength,
                       2 * pointRecSideLength,
                       2 * pointRecSideLength);
}

void Shape::showPoints(QPainter *qPainter)
{
    if (!isReady())
    {
        return;
    }

    if (isChosen)
    {
        for (QPoint *point : pointVec)
        {
            showPoint(*point, qPainter);
        }
    }
    if (currentCapturedPoint)
    {
        showPoint(*currentCapturedPoint, qPainter);
    }
}

QPoint* Shape::getCapturedPoint()
{
    return currentCapturedPoint;
}

Shape* Shape::getCurrentCapturedShape()
{
    return Shape::currentCapturedShape;
}

QPoint* Shape::getCurrentCapturedPoint()
{
    Shape* shape = Shape::getCurrentCapturedShape();
    if (!shape)
    {
        return nullptr;
    }
    return shape->getCapturedPoint();
}

Vector Shape::getUnitVec(QPoint &startPoint, QPoint &endPoint)
{
    Vector retVec(2, 1);
    double length = Shape::calDistance(startPoint, endPoint);
    retVec[0] = (endPoint.x() - startPoint.x()) / length;
    retVec[1] = (endPoint.y() - startPoint.y()) / length;

    return retVec;
}

Vector Shape::getPerpendicularVec(QPoint &startPoint, QPoint &endPoint)
{
    Matrix rotateMatrix = Shape::getRotateMatrix(M_PI / 2);
    Vector unitVec = Shape::getUnitVec(startPoint, endPoint);
    return rotateMatrix * unitVec;
}

Matrix Shape::getRotateMatrix(double theta)
{
    std::vector<double> vec{
        cos(theta), -sin(theta),
        sin(theta),  cos(theta)
    };
    return Matrix(vec, 2, 2);
}

void Shape::setSolid(const int solidId)
{
    this->solidId = solidId;
}
