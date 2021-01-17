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

    , mBar(menuBar())
    , sBar(statusBar())
    , fileMenu(mBar->addMenu("文件"))
    , editMenu(mBar->addMenu("编辑"))
    , insertMenu(mBar->addMenu("插入"))

    , openAction(fileMenu->addAction("开始 (S)"))
    , lineAction(insertMenu->addAction("直线 (L)"))
    , circleAction(insertMenu->addAction("圆形 (C)"))
    , rectAction(insertMenu->addAction("矩形 (R)"))

    , guideLabel(new QLabel())
{
    this->resize(width, height);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent

    connectSignals();
    setMenuBar(mBar);
    setStatusBar(sBar);

    sBar->addWidget(guideLabel);
    guideLabel->setFixedSize(160, BAR_HEIGHT);
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
    update();
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
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
    qDebug() <<"mousePressEvent";
    currentShape = nullptr;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
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

