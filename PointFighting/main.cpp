#include "mainwindow.h"
#include "fighting_table.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    FightingTable f;
    f.show();

    return a.exec();
}
