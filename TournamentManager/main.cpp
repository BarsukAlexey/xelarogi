#include "mainwindow.h"
#include <QApplication>

#include "dialogschedule2.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.show();
    return Dialogschedule2(21, 0).exec();


    return a.exec();
}
