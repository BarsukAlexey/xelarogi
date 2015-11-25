#include "handbookdialog.h"
#include "ui_handbookdialog.h"

#include <QDebug>

HandbookDialog::HandbookDialog(QString tableName, QString tableRusName, const QSqlDatabase &database, QWidget *parent) :
    m_database(database),
    QDialog(parent),
    ui(new Ui::HandbookDialog)
{
    ui->setupUi(this);

    ui->label->setText(tableRusName);
    this->setWindowTitle("Редактирование справочника: " + tableRusName);

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);

    QSqlRecord record = database.record(tableName);
    ui->tableWidget->setColumnCount(record.count());
    for (int i = 0; i < record.count(); i++)
    {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(rusFieldNames[record.fieldName(i)]));
    }

    QSqlQuery query("select * from " + tableName);
    if (!query.exec())
        qDebug() << database.lastError().text();
    else
    {
        while (query.next())
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            for (int i = 0; i < record.count(); i++)
            {
                QString fieldName = record.fieldName(i);
                if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
                {
                    QString tableNameFK = DataBaseExpert::getTableNameByField(fieldName);
                    QStringList values;
                    QSqlQuery queryValues("select UID, NAME from " + tableNameFK);
                    int selectedIndex = 0;
                    int index = 0;
                    if (!queryValues.exec())
                        qDebug() << queryValues.lastError().text();
                    else
                    {
                        while (queryValues.next())
                        {
                            values << queryValues.value("NAME").toString();
                            if (queryValues.value("UID").toString() == query.value(record.fieldName(i)).toString())
                                selectedIndex = index;
                            ++index;
                        }
                    }
                    QComboBox * comboBox = new QComboBox();
                    comboBox->addItems(values);
                    comboBox->setCurrentIndex(selectedIndex);

                    connect(comboBox, &QComboBox::currentTextChanged, [this, record, i](const QString & s)
                    {
                        qDebug() << "Edited" << record.fieldName(i) << s;
                    });

                    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, i, comboBox);
                }
                else
                {
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, new QTableWidgetItem(query.value(record.fieldName(i)).toString()));
                }
            }
        }
    }

    connect(ui->tableWidget, &QTableWidget::itemChanged, [this](QTableWidgetItem * item)
    {
        qDebug() << "Edited" << item->column() << item->row();
    });
}

HandbookDialog::~HandbookDialog()
{
    delete ui;
}
