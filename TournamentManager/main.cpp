#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "logindialog.h"
#include "mainwindow.h"



void break_point(QtMsgType msgType, const QMessageLogContext &, const QString &msg)
{
    if (msgType == QtDebugMsg)
    {
        std::cerr << msg.toStdString() << std::endl;
        return ;
    }
    std::cerr << msg.toStdString() << std::endl;
    return ;
}

void on_terminate()
{
    std::cerr << "on_terminate";
    return ;
}

void auth()
{
    while (true)
    {
        LoginDialog loginDialog;
        if (loginDialog.exec() == QDialog::Accepted)
        {
            break;
        }
        if (!LoginDialog::mOkBtnClicked)
        {
            exit(0);
        }
        else
        {
            QMessageBox::warning(0, "Неудачная попытка авторизации", "Логи или пароль введены неверно");
        }
    }
}

void connectDB()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    if (database.lastError().isValid())
    {
        QMessageBox::critical(0, "", database.lastError().text());
        exit(0);
    }

    database.setDatabaseName("./database/kickboxing.db");
    if (database.lastError().isValid())
    {
        QMessageBox::critical(0, "", database.lastError().text());
        exit(0);
    }

    if (database.open())
    {
        //qDebug() << "opened";
    }
    else
    {
        QMessageBox::critical(0, "", database.lastError().text());
        exit(0);
    }

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
}




//#include "dialogschedule2.h"
#include "ebnutvbazu.h"
//#include "dialogtournamentgrid.h"
//#include "formdipl.h"


int main(int argc, char *argv[])
{
    srand(time(0));
    qInstallMessageHandler(break_point);
    std::set_terminate(on_terminate);

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Secret Organization Name");
    QCoreApplication::setOrganizationDomain("SecretOrganizationDomain.com");
    QCoreApplication::setApplicationName("Perfect Tournament Manager");


    //auth();
    connectDB();

//    FormDipl d(21);
//    d.show();

//    EbnutVBazu::testMakeGrid(); return 228;

//    DialogTournamentGrid dlg(0, "", 21);
//    dlg.resize(1900, dlg.size().height());
//    dlg.show();

    MainWindow w;
    w.show();

    return a.exec();
}
