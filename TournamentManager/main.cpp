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
    qDebug() << "on_terminate";
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



//#include "createtournamentordersdialog.h"
//#include "createtournamentcategoriesdialog.h"
//#include "ebnutvbazu.h"
//#include "dialogorderoftc.h"
//#include <utility>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(break_point);
    std::set_terminate(on_terminate);

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Secret Organization Name");
    QCoreApplication::setOrganizationDomain("SecretOrganizationDomain.com");
    QCoreApplication::setApplicationName("Perfect Tournament Manager");

    //auth();
    connectDB();
    //EbnutVBazu::copyTable("AGE_CATEGORIES");
    //EbnutVBazu::copyTable("TOURNAMENT_CATEGORIES");


    MainWindow w;
    w.show();

//    DialogOrderOfTC dlg;
//    dlg.setTournamentCategories(QVector<std::pair<int, int>>()
//                                << std::make_pair(270, 1)
//                                << std::make_pair(270, 0)

//                                << std::make_pair(271, 1)
//                                << std::make_pair(271, 0)

//                                << std::make_pair(279, 1)
//                                << std::make_pair(279, 0),
//                                "По кругу"
//                                );
//    dlg.exec();





    //CreateTournamentCategoriesDialog dlg(21);
    //dlg.open();

    //CreateTournamentOrdersDialog dlg2(21);
    //dlg2.resize(dlg.size().width() * 2, dlg.size().height());
    //dlg2.open();


    return a.exec();
}
