#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QPen>

enum
{
    SHAPE_LINE = 0,
    SHAPE_CIRCLE
};

class Shape
{
public:
    Shape();
    virtual void draw(QPainter *qPainter) = 0;
    virtual ~Shape() {}
};

#endif // SHAPE_H
