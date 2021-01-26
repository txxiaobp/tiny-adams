#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QDebug>

#include "line.h"
#include "link.h"
#include "circle.h"
#include "rectangle.h"
#include "revolute_pair.h"

const int BAR_HEIGHT = 20;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width(800)
    , height(600)
    , currentObject(nullptr)
    , isCtrlPressed(false)

    , mBar(menuBar())
    , sBar(statusBar())
    , fileMenu(mBar->addMenu("文件"))
    , editMenu(mBar->addMenu("编辑"))
    , insertMenu(mBar->addMenu("插入"))
    , constraintMenu(mBar->addMenu("约束"))
    , solidMenu(mBar->addMenu("实体"))

    , newAction(fileMenu->addAction("新建"))
    , openAction(fileMenu->addAction("打开"))
    , closeAction(fileMenu->addAction("关闭"))
    , saveAction(fileMenu->addAction("保存"))
    , saveAsAction(fileMenu->addAction("另存为"))
    , exitAction(fileMenu->addAction("退出"))

    , revokeAction(editMenu->addAction("撤销"))
    , recoverAction(editMenu->addAction("恢复"))
    , copyAction(editMenu->addAction("复制"))
    , cutAction(editMenu->addAction("剪切"))
    , pasteAction(editMenu->addAction("粘贴"))
    , deleteAction(editMenu->addAction("删除"))

    , lineAction(insertMenu->addAction("直线 (L)"))
    , circleAction(insertMenu->addAction("圆形 (C)"))
    , rectAction(insertMenu->addAction("矩形 (R)"))

    , revoluteAction(constraintMenu->addAction("转动副"))

    , linkAction(solidMenu->addAction("连杆"))

    , guideLabel(new QLabel())
    , mousePosLabel(new QLabel())
{
    this->resize(width, height);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent

    connectSignals();
    setMenuBar(mBar);
    setStatusBar(sBar);

    sBar->addWidget(guideLabel);
    sBar->addWidget(mousePosLabel);
    guideLabel->setFixedSize(200, BAR_HEIGHT);
    mousePosLabel->setFixedSize(160, BAR_HEIGHT);
}

void MainWindow::connectSignals()
{
    connect(lineAction, &QAction::triggered, [&](){
        createObject(SHAPE_LINE);
    });

    connect(circleAction, &QAction::triggered, [&](){
        createObject(SHAPE_CIRCLE);
    });

    connect(rectAction, &QAction::triggered, [&](){
        createObject(SHAPE_RECTANGLE);
    });

    connect(revoluteAction, &QAction::triggered, [&](){
        RevolutePair* revolutePair = RevolutePair::createRevolute();

    });

    connect(linkAction, &QAction::triggered, [&](){
        createObject(SOLID_LINK);
    });





//    connect(revokeAction, &QAction::triggered, [&](){
//        shapeBase.pop();
//        update();
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter qPainter(this);
    qPainter.setRenderHint(QPainter::HighQualityAntialiasing);

    std::vector<Shape*> shapes = Shape::getShapes();
    for (auto shape : shapes)
    {
        shape->draw(&qPainter);
    }
    if (currentObject)
    {
        currentObject->drawAuxiliary(&qPainter, mousePos, isCtrlPressed);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    mousePos = event->pos();

    Shape::captureNearestShape(mousePos);

    //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
    if(mousePos.rx() > 0
        && mousePos.rx() < width
        && mousePos.ry() > 0
        && mousePos.ry() < height)
    {
        this->setCursor(Qt::CrossCursor);
        QString str = "X: ";
        str += std::to_string(mousePos.rx()).data();
        str += ", Y: ";
        str += std::to_string(mousePos.rx()).data();
        mousePosLabel->setText(str);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }
    update();
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mousePos = e->pos();

    Shape::chooseShape(mousePos, isCtrlPressed);

    if (!currentObject)
    {
        return;
    }

    Shape::captureNearestShape(mousePos);
    QPoint *capturedPoint = Shape::getCurrentCapturedPoint();

    if (capturedPoint)
    {
        currentObject->clickPoint(*capturedPoint, isCtrlPressed);
    }
    else
    {
        currentObject->clickPoint(mousePos, isCtrlPressed);
    }

    setStatusBarString(currentObject->getStatus());

    if (!currentObject->isReady())
    {
        return;
    }

    currentObject = nullptr;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Control)
    {
        isCtrlPressed = true;
        update();
    }

    if(ev->key() == Qt::Key_C)
    {
        createObject(SHAPE_CIRCLE);
        return;
    }

    if(ev->key() == Qt::Key_L)
    {
        createObject(SHAPE_LINE);
        return;
    }

    if(ev->key() == Qt::Key_R)
    {
        createObject(SHAPE_RECTANGLE);
        return;
    }

    if(ev->key() == Qt::Key_D)
    {
        Shape::deleteShapes();
        update();
        return;
    }
}

void MainWindow::createObject(Object_E objectEnum)
{
    switch (objectEnum)
    {
    case SHAPE_LINE:
        currentObject = new Line();
        break;
    case SHAPE_CIRCLE:
        currentObject = new Circle();
        break;
    case SHAPE_RECTANGLE:
        currentObject = new Rectangle();
        break;
    case SOLID_LINK:
        currentObject = new Link();
        break;
    default:
        currentObject = nullptr;
        break;
    }

    if (currentObject)
    {
        setStatusBarString(currentObject->getStatus());
    }
    update();
}

void MainWindow::setStatusBarString(QString string)
{
    guideLabel->setText(string);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        isCtrlPressed = false;
        update();
    }
}

