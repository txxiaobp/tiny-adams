#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <string>
#include <cmath>
#include <unordered_map>
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
    Shape(QColor shapeColor, int shapeType, int shapeChosenType);
    virtual ~Shape();
    virtual void addPoint(QPoint qPoint) = 0;
    virtual void draw(QPainter *qPainter) = 0;
    virtual double calDistance(QPoint &qPoint) = 0;
    virtual void drawAuxiliary(QPainter *qPainter, QPoint &qPoint) = 0;  // 绘制辅助线

    virtual QString getStatus() = 0;
    virtual QPoint* getTempPoint() = 0;

    void setChosen(bool isChosen);
    int getShapeId() const;
    bool isReady() { return ready; }
    static double calDistance(QPoint &pt1, QPoint &pt2) { return sqrt(pow(pt1.rx() - pt2.rx(), 2) + pow(pt1.ry() - pt2.ry(), 2)); }
    static Shape* getNearestShape(QPoint& mousePoint);
    static void captureNearestShape(QPoint& mousePoint);

protected:
    bool isChosen;
    bool ready;
    QColor shapeColor;
    int shapeType;
    int shapeChosenType;
    int shapeId;

    static std::unordered_map<int, Shape*> shapeMap;
    static int globalShapeCount;
};

#endif // SHAPE_H
