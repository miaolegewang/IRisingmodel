#include "mainwindow.h"
//#include "random.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //qDebug() << genrand() << endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
