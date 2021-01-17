#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QPoint>
#include <QLabel>
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
    void connectSignals();
    void setStatusBarString(QString string);

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    ShapeBase shapeBase;
    Shape *currentShape;
    QPoint mousePos;

    QMenuBar *mBar;
    QStatusBar *sBar;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *insertMenu;

    QAction *openAction;
    QAction *lineAction;
    QAction *circleAction;
    QAction *rectAction;

    QLabel *guideLabel;
};
#endif // MAINWINDOW_H
