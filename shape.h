#ifndef SHAPE_H
#define SHAPE_H

#include "pub_include.h"
#include <QObject>
#include <QPainter>
#include <QPen>
#include <string>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <QColor>

typedef enum
{
    SHAPE_NONE = -1,
    SHAPE_LINE = 0,
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,

    SHAPE_MAX,
}ShapeEnum;

class Shape
{
public:
    Shape(QColor shapeColor, Qt::PenStyle shapeStyle, int shapeWidth, int shapeChosenWidth);
    virtual ~Shape();

    virtual void addPoint(QPoint qPoint) = 0;
    virtual void draw(QPainter *qPainter) = 0;
    virtual double calDistance(QPoint &qPoint) = 0;
    virtual void drawAuxiliary(QPainter *qPainter, QPoint &qPoint) = 0;  // 绘制辅助线

    virtual QString getStatus() = 0;
    virtual QPoint* getTempPoint() = 0;

    void setColor(QColor shapeColor);
    void setType(); // 线性
    void setWidth(); // 线宽
    void setPainter(QPainter *qPainter);
    void setChosen(bool isChosen);
    void setCaptured(bool isCaptured);
    bool isChosenOrCaptured() const;
    int getShapeId() const;
    bool isReady() { return ready; }

    static double calDistance(QPoint &pt1, QPoint &pt2) { return sqrt(pow(pt1.rx() - pt2.rx(), 2) + pow(pt1.ry() - pt2.ry(), 2)); }
    static Shape* getNearestShape(QPoint& mousePoint);
    static void captureNearestShape(QPoint& mousePoint);
    static void chooseShape(QPoint& mousePoint, bool isMultiple = false);   // isMultiple: 多选
    static void pushChosenSet(Shape *shape);
    static void clearChosenSet();
    static void deleteShapes();
    static std::vector<Shape*> getShapes();

protected:
    bool isChosen;
    bool isCaptured;
    bool ready;

    QColor shapeColor;
    Qt::PenStyle shapeStyle;
    int shapeWidth;
    int shapeChosenWidth;

    int shapeId;

    static std::unordered_map<int, Shape*> shapeMap;
    static std::unordered_set<Shape*> chosenShapeSet;
    static int globalShapeCount;
    static Shape *currentNearest;
};

#endif // SHAPE_H
