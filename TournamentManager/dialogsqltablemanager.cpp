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
    setWindowFlags(Qt::Window);
    // TODO
    //ui->sqlTableManager->setSqlTable(table, whereStatement, hidenColumns);
    ui->label->setText(table);
}

DialogSqlTableManager::~DialogSqlTableManager()
{
    delete ui;
}
