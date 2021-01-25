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
    void mousePressEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    
    void drawShape(ShapeEnum shapeEnum);

private:
    void connectSignals();
    void setStatusBarString(QString string);

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    Shape *currentShape;
    QPoint mousePos;
    bool isCtrlPressed;

    QMenuBar *mBar;
    QStatusBar *sBar;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *insertMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *closeAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;


    QAction *revokeAction;
    QAction *recoverAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *deleteAction;


    QAction *lineAction;
    QAction *circleAction;
    QAction *rectAction;

    QLabel *guideLabel;
    QLabel *mousePosLabel;
};
#endif // MAINWINDOW_H
