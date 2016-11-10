#include "dialogsqltablemanager.h"
#include "ui_dialogsqltablemanager.h"



DialogSqlTableManager::DialogSqlTableManager(
        QWidget *parent,
        const QString& table,
        const QString& whereStatement,
        QMap<QString, QVariant> columnValue) :

    QDialog(parent),
    ui(new Ui::DialogSqlTableManager)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
    ui->sqlTableManager->setSqlTable(table, whereStatement, columnValue);

    QMap<QString, QSqlRecord > map = DBUtils::get_NAME_RUS__RELATION_TABLE_NAME();
    ui->label->setText(map[table].value("RELATION_TABLE_NAME").toString());
}

DialogSqlTableManager::~DialogSqlTableManager()
{
    delete ui;
}
