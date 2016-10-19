#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include "dialogschedule2.h"
#include "dialogschedule2inputtype.h"
#include "iostream"
using namespace std;


void break_point(QtMsgType msgType, const QMessageLogContext &, const QString &msg)
{
    if (msgType == QtDebugMsg)
    {
        std::cerr << msg.toStdString() << std::endl;
        return ;
    }
    std::cerr << msg.toStdString() << std::endl;
}

void on_terminate()
{
    int a = 228;
    int b = 223;
    int c;
    c = a + b;
    c += a += b;
}



int main(int argc, char *argv[])
{
    qInstallMessageHandler(break_point);
    std::set_terminate(on_terminate);


    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("My pussy tast like pepsi cola");
    QCoreApplication::setOrganizationDomain("pussy.com");
    QCoreApplication::setApplicationName("Tournament Manager");



    MainWindow w;
    //w.show();

    Dialogschedule2 dlg(21, 0);
    dlg.showMaximized();
    return dlg.exec();


    return a.exec();
}
