#include "rectangle.h"
#include <cassert>

Rectangle::Rectangle(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , leftUpPoint(QPoint())
    , rightDownPoint(QPoint())
{
    pointVec.push_back(&leftUpPoint);
    pointVec.push_back(&rightDownPoint);
}


void Rectangle::clickPoint(QPoint qPoint, bool extraFlag)
{
    if (leftUpPoint.isNull())
    {
        leftUpPoint = qPoint;
    }
    else if (rightDownPoint.isNull())
    {
        assert(leftUpPoint != qPoint
                && leftUpPoint.rx() != rightDownPoint.rx()
                && leftUpPoint.ry() != rightDownPoint.ry());

        rightDownPoint = qPoint;
        ready = true;
    }
}

void Rectangle::draw(QPainter *qPainter)
{
    if (!isReady())
    {
        return;
    }

    setPainter(qPainter);
    qPainter->drawRect(leftUpPoint.rx(), leftUpPoint.ry(), rightDownPoint.rx() - leftUpPoint.rx(), rightDownPoint.ry() - leftUpPoint.ry());
    showPoints(qPainter);
}

QString Rectangle::getStatus()
{
    if (leftUpPoint.isNull())
    {
        return QString("矩形：1. 请选择矩形的一个角点");
    }
    else if (rightDownPoint.isNull())
    {
        return QString("矩形：2. 请选择矩形的另一个角点");
    }
    return QString();
}

QPoint* Rectangle::getTempPoint()
{
    if (isReady())
    {
        return &leftUpPoint;
    }
    return nullptr;
}

void Rectangle::drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool extraFlag)
{
    extraFlag = false;
    QPoint *tempPoint = getTempPoint();

    if (tempPoint && !qPoint.isNull())
    {
        qPainter->setPen(QPen(Qt::blue, 1));//设置画笔形式
        qPainter->drawRect(leftUpPoint.rx(), leftUpPoint.ry(), qPoint.rx() - leftUpPoint.rx(), qPoint.ry() - leftUpPoint.ry());
    }
}

double Rectangle::calDistance(QPoint &qPoint)
{
    return 0;
}

bool Rectangle::isReady()
{
    return !leftUpPoint.isNull() && !rightDownPoint.isNull();
}

void Rectangle::capturePoint(QPoint &mousePoint)
{

}
