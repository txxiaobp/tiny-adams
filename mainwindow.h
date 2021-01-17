#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QPoint>
#include <vector>
#include <map>
#include "line.h"
#include "shape_base.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    
    void drawShape(ShapeEnum shapeEnum);

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    ShapeBase shapeBase;
    Shape *currentShape;
    QPoint *tempPoint;
    QPoint mousePos;

    QMenuBar *mBar;
    QStatusBar *sBar;
    QMenu *lineMenu;

};
#endif // MAINWINDOW_H
