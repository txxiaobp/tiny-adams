#ifndef LINK_H
#define LINK_H

#include "solid.h"
#include "line.h"
#include "circle.h"

class Link : public Solid
{
public:
    Link(double x = 0, double y = 0, double angle = 0);
    ~Link();

    void clickPoint(QPoint qPoint, bool extraFlag);
    void draw(QPainter *qPainter);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical = false);
    bool isReady();
    QString getStatus();

    static Link* createLink();

private:
    QPoint point1;
    QPoint point2;
    Line line1;
    Line line2;
    Circle circle1;
    Circle circle2;
};

#endif // LINK_H
