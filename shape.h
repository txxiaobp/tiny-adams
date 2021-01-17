#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <string>
#include <cmath>
#include <QColor>

typedef enum
{
    SHAPE_NONE = -1,
    SHAPE_LINE = 0,
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,

    SHAPE_MAX,
}ShapeEnum;

class Shape
{
public:
    Shape(QColor shapeColor, int shapeType) : ready(false), shapeColor(shapeColor), shapeType(shapeType) {}
    virtual ~Shape() {}
    virtual void addPoint(QPoint qPoint) = 0;
    virtual void draw(QPainter *qPainter) = 0;
    virtual void drawAuxiliary(QPainter *qPainter, QPoint &qPoint) = 0;

    virtual QString getStatus() = 0;
    virtual QPoint* getTempPoint() = 0;

    bool isReady() { return ready; }
    static double calDistance(QPoint &pt1, QPoint &pt2) { return sqrt(pow(pt1.rx() - pt2.rx(), 2) + pow(pt1.ry() - pt2.ry(), 2)); }

protected:
    bool ready;
    QColor shapeColor;
    int shapeType;
};

#endif // SHAPE_H
