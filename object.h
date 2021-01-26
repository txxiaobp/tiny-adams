#ifndef OBJECT_H
#define OBJECT_H

#include <QPoint>
#include <QPainter>

class Object
{
public:
    Object() {}
    virtual ~Object() {}
    virtual void clickPoint(QPoint qPoint, bool extraFlag) = 0;
    virtual void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical = false) = 0;

    virtual bool isReady() = 0;
    virtual void draw(QPainter *qPainter) = 0;
    virtual QString getStatus() = 0;
};

#endif // OBJECT_H
