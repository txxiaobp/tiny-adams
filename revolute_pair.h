#ifndef REVOLUTEPAIR_H
#define REVOLUTEPAIR_H

#include "constraint.h"
#include "matrix.h"

class RevolutePair : public Constraint
{
public:
    RevolutePair(Solid &solidA, Point &pointA, Solid &solidB, Point &pointB);
    RevolutePair(Solid &solidA, int pointAId, Solid &solidB, int pointBId);
    RevolutePair();
    ~RevolutePair() {}

    virtual void clickPoint(QPoint qPoint, bool extraFlag);
    virtual QString getStatus();
    virtual Matrix getJacobianMatrix();
    virtual Matrix getGamma();

    void drawAuxiliary(QPainter *qPainter, QPoint &qPoint, bool isHorizontalOrVertical = false) {}
    bool isReady() {}
    void draw(QPainter *qPainter) {}

    static RevolutePair* createRevolute();
};

#endif // REVOLUTEPAIR_H
