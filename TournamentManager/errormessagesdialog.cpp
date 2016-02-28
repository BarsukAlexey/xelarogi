#include "errormessagesdialog.h"
#include "ui_errormessagesdialog.h"

ErrorMessagesDialog::ErrorMessagesDialog(QStringList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessagesDialog)
{
    ui->setupUi(this);

    ui->plainTextEdit->clear();
    QString message = "";
    for (const QString& line : list)
    {
        message += "\n" + line;
    }
    ui->plainTextEdit->insertPlainText(message);
}

ErrorMessagesDialog::~ErrorMessagesDialog()
{
    delete ui;
}
