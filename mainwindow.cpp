#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QDebug>

#include "line.h"
#include "circle.h"
#include "rectangle.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width(800)
    , height(600)
    , currentShape(nullptr)
    , tempPoint (nullptr)

    , mBar(menuBar())
    , sBar(statusBar())
    , lineMenu(mBar->addMenu("直线"))
{
    ui->setupUi(this);

    this->resize(width, height);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent


    setMenuBar(mBar);
    setStatusBar(sBar);
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

    //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
    if(mousePos.rx() > 0
        && mousePos.rx() < width
        && mousePos.ry() > 0
        && mousePos.ry() < height)
    {
        this->setCursor(Qt::CrossCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }
    if (tempPoint)
    {
        update();
    }
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (!currentShape)
    {
        return;
    }

    QPoint point(e->x(), e->y());
    currentShape->addPoint(point);

    qDebug() << currentShape->getStatus().data();

    tempPoint = currentShape->getTempPoint();

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
    if(ev->key() == Qt::Key_C)
    {
        drawShape(SHAPE_CIRCLE);
        update();
        return;
    }

    if(ev->key() == Qt::Key_L)
    {
        drawShape(SHAPE_LINE);
        update();
        return;
    }

    if(ev->key() == Qt::Key_R)
    {
        drawShape(SHAPE_RECTANGLE);
        update();
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
        qDebug() << currentShape->getStatus().data();
    }
}


