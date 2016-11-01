#include "dialogsqltablemanager.h"
#include "ui_dialogsqltablemanager.h"



DialogSqlTableManager::DialogSqlTableManager(
        QWidget *parent,
        const QString& table,
        const QString& whereStatement,
        const QStringList& hidenColumns) :

    QDialog(parent),
    ui(new Ui::DialogSqlTableManager)
{
    ui->setupUi(this);
    ui->sqlTableManager->setSqlTable(table, whereStatement, hidenColumns);
}

DialogSqlTableManager::~DialogSqlTableManager()
{
    delete ui;
}
