#include "mainwindow.h"
#include "point.h"
#include "waves.h"
#include "math_graphics.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
