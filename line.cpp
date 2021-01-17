#include "line.h"

Line::Line()
    : Shape(Qt::blue, 4)
    , startPoint(QPoint())
    , endPoint(QPoint())
{
}


std::string Line::getStatus()
{
    if (startPoint.isNull())
    {
        return std::string("请选择起点");
    }
    else if (endPoint.isNull())
    {
        return std::string("请选择终点");
    }
}

QPoint* Line::getTempPoint()
{
    if (!startPoint.isNull() && endPoint.isNull())
    {
        return &startPoint;
    }
    return nullptr;
}

void Line::addPoint(QPoint qPoint)
{
    if (startPoint.isNull())
    {
        startPoint = qPoint;
    }
    else if (endPoint.isNull())
    {
        endPoint = qPoint;
        ready = true;
    }
}

void Line::draw(QPainter *qPainter)
{
    if (startPoint.isNull() || endPoint.isNull())
    {
        return;
    }

    qPainter->setPen(QPen(shapeColor, shapeType));//设置画笔形式
    qPainter->drawLine(startPoint.rx(), startPoint.ry(), endPoint.rx(), endPoint.ry());
}

void Line::drawAuxiliary(QPainter *qPainter, QPoint &qPoint)
{
    QPoint *tempPoint = getTempPoint();

    if (tempPoint && !qPoint.isNull())
    {
        qPainter->setPen(QPen(Qt::blue, 1));//设置画笔形式
        qPainter->drawLine(tempPoint->rx(), tempPoint->ry(), qPoint.rx(), qPoint.ry());
    }
}
