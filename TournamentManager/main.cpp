#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "sqltablemanager.h"
#include "dialogsqltablemanager.h"
#include "imageloaderwidget.h"

#include "ebnutvbazu.h"



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
    QSqlDatabase m_database = QSqlDatabase::addDatabase("QSQLITE");
    if (m_database.lastError().isValid())
    {
        QMessageBox::critical(0, "", m_database.lastError().text());
        exit(0);
    }

    m_database.setDatabaseName("./database/kickboxing.db");
    if (m_database.lastError().isValid())
    {
        QMessageBox::critical(0, "", m_database.lastError().text());
        exit(0);
    }

    if (m_database.open())
    {
        qDebug() << "opened";
    }
    else
    {
        QMessageBox::critical(0, "", m_database.lastError().text());
        exit(0);
    }
}

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

//    HandbookDialog handbookDlg(QString("REGION_UNITS"), QString("АТЕ"), QSqlDatabase::database(), 0, {"UID", "FLAG"});
//    handbookDlg.exec();

    //MainWindow w; w.show(); return a.exec();

    //GenerateTournamentCategoriesDialog dl(21); return dl.exec();

    SqlTableManager m(0);
    //m.setSqlTable("COUNTRIES");
    QMap<QString, QVariant> map;

    map["TOURNAMENT_FK"] = 22;
    m.setSqlTable("TOURNAMENT_CATEGORIES",
                  "TOURNAMENT_FK = 22",
                  map);
    m.showMaximized();

    //EbnutVBazu::copyTable("TOURNAMENTS");



    return a.exec();
}
