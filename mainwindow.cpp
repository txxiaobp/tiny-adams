#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QDebug>

#include "line.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width(500)
    , height(400)
{
    ui->setupUi(this);

    this->resize(width, height);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    std::vector<Shape*> shapes = shapeBase.getShapes();
    for (auto shape : shapes)
    {
        shape->draw(&painter);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QPoint mousepos = event->pos();
    qDebug() << mousepos.rx() << " " << mousepos.ry();

    //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
    if(mousepos.rx() > 0
        && mousepos.rx() < width
        && mousepos.ry() > 0
        && mousepos.ry() < height)
    {
        this->setCursor(Qt::CrossCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (point.isNull())
    {
        qDebug() << "mousePressEvent 1";
        point.setX(e->x());
        point.setY(e->y());
    }
    else
    {
        qDebug() << "mousePressEvent 2";
        QPoint point2(e->x(), e->y());
        shapeBase.push(new Line(point, point2));
        update();
        point = QPoint();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_C)
    {
        qDebug() << "c";
        return;
    }

    if(ev->key() == Qt::Key_L)
    {
        qDebug() << "line";
        update();

        return;
    }
}
