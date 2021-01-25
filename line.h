#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QPoint>
#include "shape.h"

class Line : public Shape
{
public:
    Line(QColor shapeColor = DEFAULT_COLOR,
         Qt::PenStyle shapeStyle = DEFAULT_STYLE,
         int shapeWidth = DEFAULT_WIDTH,
         int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);

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
