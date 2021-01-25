#include "circle.h"
#include <cmath>
#include <cassert>

Circle::Circle(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , radius(0.0)
{
    pointVec.push_back(&centerPoint);
}


void Circle::addPoint(QPoint qPoint, bool extraFlag)
{
    if (centerPoint.isNull())
    {
        centerPoint = qPoint;
    }
    else
    {
        assert(centerPoint != qPoint);
        radius = Shape::calDistance(centerPoint, qPoint);
        ready = true;
    }
}

void Circle::draw(QPainter *qPainter)
{
    if (centerPoint.isNull() || radius <= 0.0)
    {
        return;
    }

    setPainter(qPainter);
    qPainter->drawEllipse(centerPoint.rx() - radius, centerPoint.ry() - radius, 2 * radius, 2 * radius);
    showPoints(qPainter);
}

QString Circle::getStatus()
{
    if (centerPoint.isNull())
    {
        return QString("圆：1. 请选择圆心");
    }
    else if (radius <= 0.0)
    {
        return QString("圆：2. 请选择圆圆周上的一点");
    }
    return QString();
}

QPoint* Circle::getTempPoint()
{
    if (!centerPoint.isNull() && radius <= 0.0)
    {
        return &centerPoint;
    }
    return nullptr;
}

void Circle::drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool extraFlag)
{
    extraFlag = false;
    QPoint *tempPoint = getTempPoint();

    if (tempPoint && !qPoint.isNull())
    {
        qPainter->setPen(QPen(Qt::blue, 1));//设置画笔形式

        double tmpRadius = Shape::calDistance(centerPoint, qPoint);
        qPainter->drawEllipse(centerPoint.rx() - tmpRadius, centerPoint.ry() - tmpRadius, 2 * tmpRadius, 2 * tmpRadius);
    }
}

double Circle::calDistance(QPoint &qPoint)
{
    double disToCenter = Shape::calDistance(centerPoint, qPoint);
    return fabs(disToCenter - radius);
}

bool Circle::getReady()
{
    return !centerPoint.isNull() && fabs(radius) > 0;
}

void Circle::capturePoint(QPoint &mousePoint)
{

}
