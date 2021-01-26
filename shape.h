#ifndef SHAPE_H
#define SHAPE_H

#include "pub_include.h"
#include "object.h"
#include "matrix.h"
#include <QObject>
#include <QPainter>
#include <QPen>
#include <string>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <QColor>


class Shape : public Object
{
public:
    Shape(int solidId, QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth);
    Shape(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth);
    virtual ~Shape();

    virtual double calDistance(QPoint &qPoint) = 0;
    virtual void capturePoint(QPoint &mousePoint) = 0;
    virtual QPoint* getTempPoint() = 0;

    void setSolid(const int solidId);
    void setColor(QColor shapeColor);
    void setType(); // 线性
    void setWidth(); // 线宽
    void setPainter(QPainter *qPainter);
    void setPointPainter(QPainter *qPainter);
    void setChosen(bool isChosen);
    void setCaptured(bool isCaptured);
    bool isChosenOrCaptured() const;
    int getSolidId() const;
    int getShapeId() const;
    bool isReady() { return ready; }
    void showPoints(QPainter *qPainter);
    QPoint* getCapturedPoint();

    static double calDistance(QPoint &pt1, QPoint &pt2) { return sqrt(pow(pt1.rx() - pt2.rx(), 2) + pow(pt1.ry() - pt2.ry(), 2)); }
    static Shape* getNearestShape(QPoint& mousePoint);
    static void captureNearestShape(QPoint& mousePoint);
    static void chooseShape(QPoint& mousePoint, bool isMultiple = false);   // isMultiple: 多选
    static void pushChosenSet(Shape *shape);
    static void clearChosenSet();
    static void deleteShapes();
    static std::vector<Shape*> getShapes();
    static Shape* getCurrentCapturedShape();
    static QPoint* getCurrentCapturedPoint();

    static Vector getUnitVec(QPoint &startPoint, QPoint &endPoint);
    static Vector getPerpendicularVec(QPoint &startPoint, QPoint &endPoint);
    static Matrix getRotateMatrix(double theta);

private:
    void showPoint(QPoint &point, QPainter *qPainter);

protected:
    bool isChosen;
    bool isCaptured;
    bool ready;

    QColor shapeColor;
    Qt::PenStyle shapeStyle;
    int shapeWidth;
    int shapeChosenWidth;

    std::vector<QPoint*> pointVec;
    int shapeId;
    int solidId;
    QPoint *currentCapturedPoint;

    static std::unordered_map<int, Shape*> shapeMap;
    static std::unordered_set<Shape*> chosenShapeSet;
    static int globalShapeCount;
    static Shape *currentCapturedShape;
};

#endif // SHAPE_H
