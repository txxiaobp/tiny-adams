#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QDebug>

#include "line.h"
#include "circle.h"
#include "rectangle.h"

const int BAR_HEIGHT = 20;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width(800)
    , height(600)
    , currentShape(nullptr)
    , isCtrlPressed(false)

    , mBar(menuBar())
    , sBar(statusBar())
    , fileMenu(mBar->addMenu("文件"))
    , editMenu(mBar->addMenu("编辑"))
    , insertMenu(mBar->addMenu("插入"))

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
        drawShape(SHAPE_LINE);
    });

    connect(circleAction, &QAction::triggered, [&](){
        drawShape(SHAPE_CIRCLE);
    });

    connect(rectAction, &QAction::triggered, [&](){
        drawShape(SHAPE_RECTANGLE);
    });

    connect(revokeAction, &QAction::triggered, [&](){
        shapeBase.pop();
        update();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter qPainter(this);
    qPainter.setRenderHint(QPainter::HighQualityAntialiasing);

    std::vector<Shape*> shapes = shapeBase.getShapes();
    for (auto shape : shapes)
    {
        shape->draw(&qPainter);
    }
    if (currentShape)
    {
        currentShape->drawAuxiliary(&qPainter, mousePos);
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

    if (isCtrlPressed)
    {
        Shape::chooseShape(mousePos, true);
    }
    else
    {
        Shape::chooseShape(mousePos, false);
    }

    if (!currentShape)
    {
        return;
    }

    QPoint point(e->x(), e->y());
    currentShape->addPoint(point);

    setStatusBarString(currentShape->getStatus());

    if (!currentShape->isReady())
    {
        return;
    }

    shapeBase.push(currentShape);
    currentShape = nullptr;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Control)
    {
        isCtrlPressed = true;
    }

    if(ev->key() == Qt::Key_C)
    {
        drawShape(SHAPE_CIRCLE);
        return;
    }

    if(ev->key() == Qt::Key_L)
    {
        drawShape(SHAPE_LINE);
        return;
    }

    if(ev->key() == Qt::Key_R)
    {
        drawShape(SHAPE_RECTANGLE);
        return;
    }
}

void MainWindow::drawShape(ShapeEnum shapeEnum)
{
    switch (shapeEnum)
    {
    case SHAPE_LINE:
        currentShape = new Line();
        break;
    case SHAPE_CIRCLE:
        currentShape = new Circle();
        break;
    case SHAPE_RECTANGLE:
        currentShape = new Rectangle();
        break;
    default:
        currentShape = nullptr;
        break;
    }

    if (currentShape)
    {
        setStatusBarString(currentShape->getStatus());
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
    }
}

