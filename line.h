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
    virtual ~Line() {}

    void capturePoint(QPoint &mousePoint);
    bool getReady();
    void addPoint(QPoint qPoint, bool extraFlag = false);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical = false);
    QString getStatus();

private:
    QPoint* getTempPoint();
    QPoint getEndPointWithExtraFlag(QPoint &sPoint, QPoint &ePoint, bool extraFlag);

private:
    QPoint startPoint;
    QPoint centerPoint;
    QPoint endPoint;
};

#endif // LINE_H
