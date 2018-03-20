#include "mainwindow.h"
#include <QApplication>
#include "tool.h"
int main(int argc, char *argv[])
{
    prt(info,"11111");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
