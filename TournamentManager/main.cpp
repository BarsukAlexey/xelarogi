#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "logindialog.h"



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
        qDebug() << "opened";
    }
    else
    {
        QMessageBox::critical(0, "", database.lastError().text());
        exit(0);
    }

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
}



#include "createtournamentordersdialog.h"
#include "createtournamentcategoriesdialog.h"

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


//    QMap<QString, QVariant> map;
//    map["COUNTRY_FK"] = 278;
//    DialogSqlTableManager dlg(0, "CLUBS", "",  map);
//    dlg.setVisibleShit("LOLKA");
//    dlg.showMaximized();
//    dlg.exec();
//    qDebug() << "dlg.exec(): " << dlg.getUID();
//    return 0;


//    qDebug() << QDate::fromString("01.2.2011", "d.M.yyyy");
//    return 0;

    CreateTournamentCategoriesDialog dlg(21);
    dlg.open();

    CreateTournamentOrdersDialog dlg2(21);
    dlg2.resize(dlg.size().width() * 2, dlg.size().height());
    dlg2.open();


//    DialogSqlTableManager dd(0, "CLUBS");
//    dd.open();

//    DialogSqlTableManager ddd(0, "COACHS");
//    ddd.open();

//    DialogSqlTableManager ddd(0, "REGION_UNITS");
//     ddd.open();
    //return dlg.exec();
    //qDebug() << findUidToutnamentCategory(21, QDate(1991, 6, 9), 3, 60, 1393);

    return a.exec();
}
