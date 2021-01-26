#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <QObject>
#include <QPoint>
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(QColor shapeColor = DEFAULT_COLOR,
           Qt::PenStyle shapeStyle = DEFAULT_STYLE,
           int shapeWidth = DEFAULT_WIDTH,
           int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);
    virtual ~Rectangle() {}

    void capturePoint(QPoint &mousePoint);
    bool isReady();
    void clickPoint(QPoint qPoint, bool extraFlag = false);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool extraFlag = false);
    QString getStatus();

private:
    QPoint* getTempPoint();

private:
    QPoint leftUpPoint;
    QPoint rightDownPoint;
};

#endif // RECTANGLE_H
