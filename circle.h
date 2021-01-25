#ifndef CIRCLE_H
#define CIRCLE_H


#include <QObject>
#include <QPoint>
#include "shape.h"

class Circle : public Shape
{
public:
    Circle(QColor shapeColor = DEFAULT_COLOR,
           Qt::PenStyle shapeStyle = DEFAULT_STYLE,
           int shapeWidth = DEFAULT_WIDTH,
           int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);
    virtual ~Circle() {}

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
