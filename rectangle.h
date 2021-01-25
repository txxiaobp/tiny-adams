#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <QObject>
#include <QPoint>
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();

    void addPoint(QPoint qPoint);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint);
    QString getStatus();

private:
    QPoint* getTempPoint();

private:
    QPoint leftUpPoint;
    QPoint rightDownPoint;
};

#endif // RECTANGLE_H
