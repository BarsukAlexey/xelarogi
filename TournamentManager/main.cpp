#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "dialogschedule2.h"
#include "dialogschedule2inputtype.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("My pussy tast like pepsi cola");
    QCoreApplication::setOrganizationDomain("pussy.com");
    QCoreApplication::setApplicationName("Tournament Manager");



    MainWindow w;
    w.show();
    //Dialogschedule2 dlg(21, 0);
    //dlg.showMaximized();
    //Dialogschedule2InputType dlg(0, "Сон", 60, false);
    //return dlg.exec();


    return a.exec();
}
