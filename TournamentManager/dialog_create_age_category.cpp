#include "dialog_create_age_category.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DialogCreateAgeCategory::DialogCreateAgeCategory(QWidget* parent, long long sexUID) :
    QDialog(parent)
  ,
    ui(new Ui::CreateAgeCategory)
{
    ui->setupUi(this);

    {
        QSqlQuery query("SELECT * FROM SEXES");
        if (!query.exec())
            qDebug() << query.lastError();
        while (query.next())
        {
            long long curUIDSEX = query.value("UID").toLongLong();
            ui->comboBoxSex->addItem(query.value("NAME").toString(), curUIDSEX);
            if (sexUID == curUIDSEX)
            {
                ui->comboBoxSex->setCurrentIndex(ui->comboBoxSex->count() - 1);
                ui->comboBoxSex->setEnabled(false);
            }
        }
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this] ()
    {
        QString ageCat = ui->lineEditAgeCategory->text().trimmed();
        long long sexUID = ui->comboBoxSex->currentData(Qt::UserRole).toLongLong();
        if (ageCat.isEmpty())
        {
            QMessageBox::information(this, "Введите название", "Вы не указали название");
        }
        else
        {
            QSqlQuery query("INSERT INTO AGE_CATEGORIES(NAME, SEX_FK) VALUES(?, ?)");
            query.addBindValue(ageCat);
            query.addBindValue(sexUID);
            if (!query.exec())
                qDebug() << query.lastError();
            accept();
        }
    });

    connect(ui->buttonBox, &QDialogButtonBox::rejected, [this] ()
    {
        reject();
    });
}

DialogCreateAgeCategory::~DialogCreateAgeCategory()
{
    delete ui;
}
