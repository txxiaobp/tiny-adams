#ifndef CIRCLE_H
#define CIRCLE_H


#include <QObject>
#include <QPoint>
#include "shape.h"

class Circle : public Shape
{
public:
    Circle();

    void addPoint(QPoint qPoint);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint);

    QString getStatus();

private:
    QPoint* getTempPoint();

private:
    QPoint centerPoint;
    double radius;
};


#endif // CIRCLE_H
