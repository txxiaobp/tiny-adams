#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QPoint>
#include "shape.h"

class Line : public Shape
{
public:
    Line();

    void addPoint(QPoint qPoint);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint);
    QString getStatus();

private:
    QPoint* getTempPoint();

private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H
