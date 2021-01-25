#include "circle.h"
#include <cmath>
#include <cassert>

Circle::Circle()
    : Shape(Qt::blue, 4, 6)
    , radius(0.0)
{

}


void Circle::addPoint(QPoint qPoint)
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

    if (isChosen)
    {
        qPainter->setPen(QPen(shapeColor, shapeChosenType));//设置画笔形式
    }
    else
    {
        qPainter->setPen(QPen(shapeColor, shapeType));//设置画笔形式
    }

    qPainter->drawEllipse(centerPoint.rx() - radius, centerPoint.ry() - radius, 2 * radius, 2 * radius);
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

void Circle::drawAuxiliary(QPainter *qPainter, QPoint &qPoint)
{
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
    double disX = qPoint.x() - centerPoint.x();
    double disY = qPoint.y() - centerPoint.y();

    double disToCenter = sqrt(disX * disX + disY * disY);
    return fabs(disToCenter - radius);
}
