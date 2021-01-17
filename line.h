#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QPoint>
#include "shape.h"

class Line : public Shape
{
public:
    Line(QPoint start, QPoint end);
    Line();
    void draw(QPainter *qPainter);

private:
    QPoint start;
    QPoint end;
};

#endif // LINE_H
