#include "errormessagesdialog.h"
#include "ui_errormessagesdialog.h"

ErrorMessagesDialog::ErrorMessagesDialog(QStringList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessagesDialog)
{
    ui->setupUi(this);

    ui->plainTextEdit->clear();
    for (const QString& line : list)
    {
        ui->plainTextEdit->insertPlainText(ui->plainTextEdit->toPlainText() + "\n" + line);
    }
}

ErrorMessagesDialog::~ErrorMessagesDialog()
{
    delete ui;
}
