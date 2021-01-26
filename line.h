#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QPoint>
#include "shape.h"

class Line : public Shape
{
public:
    Line(QPoint &sPoint,
         QPoint &ePoint,
         int solidId = INVALID_ID,
         QColor shapeColor = DEFAULT_COLOR,
         Qt::PenStyle shapeStyle = DEFAULT_STYLE,
         int shapeWidth = DEFAULT_WIDTH,
         int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);

    Line(QColor shapeColor = DEFAULT_COLOR,
         Qt::PenStyle shapeStyle = DEFAULT_STYLE,
         int shapeWidth = DEFAULT_WIDTH,
         int shapeChosenWidth = DEFAULT_CHOSEN_WIDTH);
    virtual ~Line() {}

    void setPoints(const QPoint &sPoint, const QPoint &ePoint);
    void capturePoint(QPoint &mousePoint);
    bool isReady();
    void clickPoint(QPoint qPoint, bool extraFlag = false);
    void draw(QPainter *qPainter);
    double calDistance(QPoint &qPoint);
    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical = false);
    QString getStatus();

    static QPoint getEndPointWithExtraFlag(QPoint &sPoint, QPoint &ePoint, bool extraFlag);

private:
    QPoint* getTempPoint();

private:
    QPoint startPoint;
    QPoint centerPoint;
    QPoint endPoint;
};

#endif // LINE_H
