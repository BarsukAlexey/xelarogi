#include "createtypedialog.h"
#include "ui_createtypedialog.h"

CreateTypeDialog::CreateTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTypeDialog)
{
    ui->setupUi(this);

    connect(ui->cancelBtn, &QPushButton::clicked, [this] ()
    {
        reject();
    });

    connect(ui->acceptBtn, &QPushButton::clicked, [this] ()
    {
        QString typeName = ui->typeNameLE->text().trimmed();

        if (typeName.isEmpty())
        {
            QMessageBox::information(this, "Введите название раздела", "Вы не указали название раздела");
        }
        else
        {
            QSqlQuery query;
            if (!query.prepare("INSERT INTO TYPES(NAME) VALUES(?)"))
                qDebug() << query.lastError().text();
            query.bindValue(0, typeName);

            if (!query.exec())
                qDebug() << query.lastError().text();

            accept();
        }
    });
}

CreateTypeDialog::~CreateTypeDialog()
{
    delete ui;
}
