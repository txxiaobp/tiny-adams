#include "mainwindow.h"
#include "matrix.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::vector<double> vec{
        1, 4, 5,
        3, 6, 1,
        4, 6, 3
    };
    Matrix matrix(vec, 3, 3);
    matrix.showMatrix();

    Matrix matrix2 = matrix.reverseMatrix();
    matrix2.showMatrix();

    Matrix matrix3 = matrix * matrix2;
    matrix3.showMatrix();
    return 0;

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
