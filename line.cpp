#include "line.h"

//Line::Line(QPoint start, QPoint end)
Line::Line()
    : start(QPoint())
    , end(QPoint())
{

}

Line::Line(QPoint start, QPoint end)
    : start(start)
    , end(end)
{

}

void Line::draw(QPainter *qPainter)
{
    if (start.isNull() || end.isNull())
    {
        return;
    }

    qPainter->setPen(QPen(Qt::blue,4));//设置画笔形式
    qPainter->drawLine(start.rx(), start.ry(), end.rx(), end.ry());
}
