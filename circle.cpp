#include "circle.h"
#include <cmath>
#include <cassert>
#include <QColor>


Circle::Circle(QPoint &centerPoint, double radius, int solidId, QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(solidId, shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , centerPoint(centerPoint)
    , radius(radius)
{
    pointVec.push_back(&centerPoint);
}


Circle::Circle(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , radius(0.0)
{
    pointVec.push_back(&centerPoint);
}


void Circle::clickPoint(QPoint qPoint, bool extraFlag)
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

    drawCenterLine(qPainter);
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

    if (!tempPoint || qPoint.isNull())
    {
        return;
    }

    qPainter->setPen(QPen(Qt::blue, 1));//设置画笔形式

    double tmpRadius = Shape::calDistance(centerPoint, qPoint);
    qPainter->drawEllipse(centerPoint.rx() - tmpRadius, centerPoint.ry() - tmpRadius, 2 * tmpRadius, 2 * tmpRadius);
    drawCenterLine(qPainter, tmpRadius);
}

double Circle::calDistance(QPoint &qPoint)
{
    double disToCenter = Shape::calDistance(centerPoint, qPoint);
    return std::min(fabs(disToCenter - radius), disToCenter);
}

bool Circle::isReady()
{
    return !centerPoint.isNull() && fabs(radius) > 0;
}

void Circle::capturePoint(QPoint &mousePoint)
{
    double distance = calDistance(mousePoint);

    if (distance < DISTANCE_THRESHOLD)
    {
        currentCapturedPoint = &centerPoint;
    }
}

void Circle::setCenter(const QPoint &qPoint)
{
    centerPoint = qPoint;
}

void Circle::setRadius(const double radius)
{
    this->radius = radius;
}

void Circle::drawCenterLine(QPainter *qPainter, double tmpRadius)
{
    QPen pen(Qt::black, 1);
    pen.setStyle(Qt::DashDotLine);
    qPainter->setPen(pen);//设置画笔形式

    double margin = tmpRadius * CIRCLE_MARGIN_RATIO;
    qPainter->drawLine(centerPoint.x() - tmpRadius - margin, centerPoint.y(), centerPoint.x() + tmpRadius + margin, centerPoint.y());
    qPainter->drawLine(centerPoint.x(), centerPoint.y() - tmpRadius - margin, centerPoint.x(), centerPoint.y() + tmpRadius + margin);
}

void Circle::drawCenterLine(QPainter *qPainter)
{
    QPen pen(Qt::black, 1);
    pen.setStyle(Qt::DashDotLine);
    qPainter->setPen(pen);//设置画笔形式

    double margin = radius * CIRCLE_MARGIN_RATIO;
    qPainter->drawLine(centerPoint.x() - radius - margin, centerPoint.y(), centerPoint.x() + radius + margin, centerPoint.y());
    qPainter->drawLine(centerPoint.x(), centerPoint.y() - radius - margin, centerPoint.x(), centerPoint.y() + radius + margin);
}
