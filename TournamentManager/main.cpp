#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "dialogmanagersqltable.h"

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
    qDebug() << "on_terminate";
}



int main(int argc, char *argv[])
{
    qInstallMessageHandler(break_point);
    std::set_terminate(on_terminate);


    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Secret Organization Name");
    QCoreApplication::setOrganizationDomain("SecretOrganizationDomain.com");
    QCoreApplication::setApplicationName("Perfect Tournament Manager");


    MainWindow w;
    //w.show(); return a.exec();

    //CreateTournamentCategoriesDialog2 dlg(0, "TOURNAMENT_CATEGORIES", "TOURNAMENT_FK = 21");
    DialogManagerSqlTable dlg(
                0,
                "TOURNAMENT_CATEGORIES",
                "TOURNAMENT_FK = 21",
                QStringList() << "TOURNAMENT_FK"
                );
    dlg.showMaximized();
    return dlg.exec();



}
