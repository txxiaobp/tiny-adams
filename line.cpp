#include "line.h"
#include <QDebug>


Line::Line(QPoint &sPoint, QPoint &ePoint, int solidId, QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(solidId, shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , startPoint(sPoint)
    , centerPoint(QPoint())
    , endPoint(ePoint)
{
    centerPoint.setX((sPoint.x() + ePoint.x()) / 2);
    centerPoint.setY((sPoint.y() + ePoint.y()) / 2);

    pointVec.push_back(&startPoint);
    pointVec.push_back(&centerPoint);
    pointVec.push_back(&endPoint);
}

Line::Line(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth)
    : Shape(shapeColor, shapeStyle, shapeWidth, shapeChosenWidth)
    , startPoint(QPoint())
    , centerPoint(QPoint())
    , endPoint(QPoint())
{
    pointVec.push_back(&startPoint);
    pointVec.push_back(&centerPoint);
    pointVec.push_back(&endPoint);
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

/* extraFlag为附加标识，对于直线来说，当extraFlag为true时，所画的直线是水平或垂直的 */
void Line::clickPoint(QPoint qPoint, bool extraFlag)
{
    if (startPoint.isNull())
    {
        startPoint = qPoint;
    }
    else if (endPoint.isNull())
    {
        endPoint = getEndPointWithExtraFlag(startPoint, qPoint, extraFlag);
        centerPoint.setX((startPoint.x() + endPoint.x()) / 2);
        centerPoint.setY((startPoint.y() + endPoint.y()) / 2);
        ready = true;
    }
}

void Line::draw(QPainter *qPainter)
{
    if (!isReady())
    {
        return;
    }

    setPainter(qPainter);
    qPainter->drawLine(startPoint.rx(), startPoint.ry(), endPoint.rx(), endPoint.ry());
    showPoints(qPainter);
}

void Line::drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool extraFlag)
{
    QPoint *sPoint = getTempPoint();  // temporary start point

    if (nullptr == sPoint || qPoint.isNull())
    {
        return;
    }
    QPoint ePoint = getEndPointWithExtraFlag(*sPoint, qPoint, extraFlag);

    qPainter->setPen(QPen(Qt::blue, 1));//设置画笔形式
    qPainter->drawLine(sPoint->rx(), sPoint->ry(), ePoint.x(), ePoint.y());
}

double Line::calDistance(QPoint &qPoint)
{
    double x1 = startPoint.x();
    double y1 = startPoint.y();

    double x2 = endPoint.x();
    double y2 = endPoint.y();

    double x0 = qPoint.x();
    double y0 = qPoint.y();

    if (fabs(x1 - x2) < EPS)  // vertical
    {
        return fabs(x1 - x0);
    }
    else if (fabs(y1 - y2) < EPS)  // horizontal
    {
        return fabs(y1 - y0);
    }
    else
    {
        double A = 1.0 / (x2 - x1);
        double B = 1.0 / (y1 - y2);
        double C = y1 / (y2 - y1) + x1 / (x1 - x2);

        return fabs(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
    }
}

QPoint Line::getEndPointWithExtraFlag(QPoint &sPoint, QPoint &ePoint, bool extraFlag)
{
    if (!extraFlag)
    {
        return ePoint;
    }

    double ePointX = ePoint.x();
    double ePointY = ePoint.y();

    if (extraFlag)
    {
        double vecX = ePointX - sPoint.x();
        double vecY = ePointY - sPoint.y();

        if (fabs(vecX) <= fabs(vecY))  // x nearer
        {
            ePointX = sPoint.x();
        }
        else
        {
            ePointY = sPoint.y();
        }
    }

    return QPoint(ePointX, ePointY);
}

bool Line::isReady()
{
    return !startPoint.isNull() && !endPoint.isNull();
}

void Line::capturePoint(QPoint &mousePoint)
{
    for (QPoint *point : this->pointVec)
    {
        double distanceToPoint = Shape::calDistance(*point, mousePoint);

        if (distanceToPoint < DISTANCE_THRESHOLD)
        {
            currentCapturedPoint = point;
            break;
        }
    }
}

void Line::setPoints(const QPoint &sPoint, const QPoint &ePoint)
{
    startPoint = sPoint;
    endPoint = ePoint;

    centerPoint.setX((startPoint.x() + endPoint.x()) / 2);
    centerPoint.setY((startPoint.y() + endPoint.y()) / 2);
}
