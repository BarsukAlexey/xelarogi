#include "dialog_insert_data_in_database.h"
#include "ui_dialog_insert_data_in_database.h"
#include <QMessageBox>

DialogInsertDataInDatabase::DialogInsertDataInDatabase(QWidget *parent, QString str, QStringList list, QString message) :
    QDialog(parent),
    mList(list),
    ui(new Ui::DialogInsertDataInDatabase)
{
    ui->setupUi(this);

    qSort(list);
    ui->lineEdit->setText(str);
    ui->comboBox->addItems(list);
    if (list.isEmpty())
        ui->pushButtonSelectOld->setEnabled(false);
    ui->plainTextEdit->setPlainText(message);
}

DialogInsertDataInDatabase::~DialogInsertDataInDatabase()
{
    delete ui;
}

void DialogInsertDataInDatabase::on_pushButtonAddNew_clicked()
{
    QString name = ui->lineEdit->text().simplified();

    bool haveInDB = false;
    for (QString s : mList)
        haveInDB |= s.simplified().toUpper() == name.simplified().toUpper();

    if (name.isEmpty())
    {
        QMessageBox d;
        d.setText("Поле не может быть пустым");
        d.exec();
    }
    else if (haveInDB)
    {
        QMessageBox d;
        d.setText("Введёное имя уже есть в базе данных. Выберите его из списка.");
        d.exec();
    }
    else
    {
        result = ui->lineEdit->text().trimmed();
        done(-1);
    }
}

void DialogInsertDataInDatabase::on_pushButtonSelectOld_clicked()
{
    result = ui->comboBox->currentText();
    done(228);
}

QString DialogInsertDataInDatabase::getText()
{
    return result;
}
