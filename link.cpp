#include "link.h"
#include <cassert>
#include <QDebug>


const double LINK_LENGTH_WIDTH_RATIO = 0.05;


Link::Link(double x, double y, double angle)
    : Solid(x, y, angle)
    , point1(QPoint())
    , point2(QPoint())
    , line1(Line())
    , line2(Line())
    , circle1(Circle())
    , circle2(Circle())
{
    shapeSet.insert(&line1);
    shapeSet.insert(&line2);
    shapeSet.insert(&circle1);
    shapeSet.insert(&circle2);
}

Link::~Link()
{

}

Link* Link::createLink()
{
    Link* link = new Link();
    assert(nullptr != link);
    Solid::restoreSolid(link);
    return link;
}

bool Link::isReady()
{
    return !point1.isNull() && !point2.isNull();
}

QString Link::getStatus()
{
    if (point1.isNull())
    {
        return QString("请选择连杆的一个端点");
    }
    if (!point1.isNull() && point2.isNull())
    {
        return QString("请选择连杆的另一个端点");
    }
    assert(isReady());
    return QString("已就绪");
}

void Link::clickPoint(QPoint qPoint, bool extraFlag)
{
    if (point1.isNull())
    {
        point1 = qPoint;
    }
    else if (point2.isNull())
    {
        point2 = Line::getEndPointWithExtraFlag(point1, qPoint, extraFlag);

        double linkLength = Shape::calDistance(point1, point2);
        double radius = LINK_LENGTH_WIDTH_RATIO * linkLength;

        circle1.setCenter(point1);
        circle1.setRadius(radius);
        circle1.setSolid(getSolidId());

        circle2.setCenter(point2);
        circle2.setRadius(radius);
        circle2.setSolid(getSolidId());

        Vector perpenVec = Shape::getPerpendicularVec(point1, point2);
        perpenVec *= radius;

        QPoint tmpPoint11(point1.x() + perpenVec[0], point1.y() + perpenVec[1]);
        QPoint tmpPoint21(point2.x() + perpenVec[0], point2.y() + perpenVec[1]);
        perpenVec *= -1;
        QPoint tmpPoint12(point1.x() + perpenVec[0], point1.y() + perpenVec[1]);
        QPoint tmpPoint22(point2.x() + perpenVec[0], point2.y() + perpenVec[1]);

        line1.setPoints(tmpPoint11, tmpPoint21);
        line1.setSolid(getSolidId());
        line2.setPoints(tmpPoint12, tmpPoint22);
        line2.setSolid(getSolidId());
    }
}

void Link::draw(QPainter *qPainter)
{
    line1.draw(qPainter);
    line2.draw(qPainter);
    circle1.draw(qPainter);
    circle2.draw(qPainter);
}

void Link::drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical)
{
    if (point1.isNull() || isReady())
    {
        return;
    }

    QPoint tmpPoint = Line::getEndPointWithExtraFlag(point1, qPoint, isHorizontalOrVertical);

    double tmpLinkLength = Shape::calDistance(point1, tmpPoint);
    double tmpRadius = LINK_LENGTH_WIDTH_RATIO * tmpLinkLength;

    Vector perpenVec = Shape::getPerpendicularVec(point1, tmpPoint);
    perpenVec *= tmpRadius;

    QPoint tmpPoint11(point1.x() + perpenVec[0], point1.y() + perpenVec[1]);
    QPoint tmpPoint21(tmpPoint.x() + perpenVec[0], tmpPoint.y() + perpenVec[1]);
    perpenVec *= -1;
    QPoint tmpPoint12(point1.x() + perpenVec[0], point1.y() + perpenVec[1]);
    QPoint tmpPoint22(tmpPoint.x() + perpenVec[0], tmpPoint.y() + perpenVec[1]);

    Line tmpLine1(tmpPoint11, tmpPoint21);
    Line tmpLine2(tmpPoint12, tmpPoint22);

    Circle tmpCircle1(point1, tmpRadius);
    Circle tmpCircle2(tmpPoint, tmpRadius);

    tmpLine1.draw(qPainter);
    tmpLine2.draw(qPainter);
    tmpCircle1.draw(qPainter);
    tmpCircle2.draw(qPainter);
}
