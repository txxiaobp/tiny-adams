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
    
    void createObject(Object_E objectEnum);

private:
    void connectSignals();
    void setStatusBarString(QString string);

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    Object *currentObject;
    QPoint mousePos;
    bool isCtrlPressed;

    QMenuBar *mBar;
    QStatusBar *sBar;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *insertMenu;
    QMenu *constraintMenu;
    QMenu *solidMenu;

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

    QAction *revoluteAction;

    QAction *linkAction;

    QLabel *guideLabel;
    QLabel *mousePosLabel;
};
#endif // MAINWINDOW_H
