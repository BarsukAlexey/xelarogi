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
    ui->labelTitle->setText(map[table].value("NAME_RUS").toString());

    ui->widget->setVisible(false);
    ui->labelMessage->setVisible(false);

    connect(ui->pushButtonSelect, &QPushButton::clicked, [this](){
        index = ui->sqlTableManager->getUidIndexOfSelectedRow();
        if (!index.isValid())
            return;

        accept();
    });

    connect(ui->pushButtonJustAdd, &QPushButton::clicked, [this](){
        if (ui->sqlTableManager->addNewName(newName))
        {
            index = ui->sqlTableManager->getUidIndexOfSelectedRow();
            if (index.isValid())
                accept();
        }
    });

    connect(ui->pushButtonStop, &QPushButton::clicked, [this](){
        reject();
    });
}

DialogSqlTableManager::~DialogSqlTableManager()
{
    delete ui;
}

void DialogSqlTableManager::setVisibleShit(const QString& text, const QString& newName)
{
    ui->widget->setVisible(true);
    ui->labelMessage->setVisible(true);
    ui->labelMessage->setText(text);
    this->newName = newName;
}

int DialogSqlTableManager::getUID()
{
    return index.data(Qt::EditRole).toInt();
}
