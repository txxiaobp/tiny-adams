#include "line.h"

Line::Line()
    : Shape(Qt::blue, 4, 7)
    , startPoint(QPoint())
    , endPoint(QPoint())
{

}


QString Line::getStatus()
{
    if (startPoint.isNull())
    {
        return QString("直线：1. 请选择起点");
    }
    else if (endPoint.isNull())
    {
        return QString("直线：2. 请选择终点");
    }
    return QString();
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

    if (isChosen)
    {
        qPainter->setPen(QPen(shapeColor, shapeChosenType));//设置画笔形式
    }
    else
    {
        qPainter->setPen(QPen(shapeColor, shapeType));//设置画笔形式
    }

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

double Line::calDistance(QPoint &qPoint)
{
    double x1 = startPoint.x();
    double y1 = startPoint.y();

    double x2 = endPoint.x();
    double y2 = endPoint.y();

    double x0 = qPoint.x();
    double y0 = qPoint.y();


    double A = 1.0 / (x2 - x1);
    double B = 1.0 / (y1 - y2);
    double C = y1 / (y2 - y1) + x1 / (x1 - x2);

    return fabs(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
}
