#ifndef CIRCLE_H
#define CIRCLE_H


#include <QObject>
#include <QPoint>
#include "shape.h"

class Circle : public Shape
{
public:
    Circle(QPoint &centerPoint,
           double radius,
           int solidId = INVALID_ID,
           QColor shapeColor = DEFAULT_COLOR,
           Qt::PenStyle shapeStyle = DEFAULT_STYLE,
           int shapeWidth = DEFAULT_WIDTH,
           int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);
    Circle(QColor shapeColor = DEFAULT_COLOR,
           Qt::PenStyle shapeStyle = DEFAULT_STYLE,
           int shapeWidth = DEFAULT_WIDTH,
           int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);
    virtual ~Circle() {}

    void setCenter(const QPoint &qPoint);
    void setRadius(const double radius);
    void capturePoint(QPoint &mousePoint);
    bool isReady();
    void clickPoint(QPoint qPoint, bool extraFlag = false);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool extraFlag = false);
    QString getStatus();

private:
    void drawCenterLine(QPainter *qPainter, double tmpRadius);
    void drawCenterLine(QPainter *qPainter);
    QPoint* getTempPoint();

private:
    QPoint centerPoint;
    double radius;
};


#endif // CIRCLE_H
