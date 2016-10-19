#include "dialogschedule2inputtype.h"
#include "ui_dialogschedule2inputtype.h"

Dialogschedule2InputType::Dialogschedule2InputType(QWidget *parent, QString str, int timeSec, bool canEditText) :
    QDialog(parent),
    ui(new Ui::Dialogschedule2InputType)
{
    ui->setupUi(this);
    ui->textEdit->setText(str);
    ui->textEdit->setEnabled(canEditText);
    ui->timeEdit->setTime(QTime(timeSec / 60 / 60, timeSec / 60 % 60));
}

Dialogschedule2InputType::~Dialogschedule2InputType()
{
    delete ui;
}

QString Dialogschedule2InputType::getText()
{
    return ui->textEdit->toPlainText();
}

int Dialogschedule2InputType::getDurationInSeconds()
{
    QTime time = ui->timeEdit->time();
    return time.hour() * 60 * 60 + time.minute() * 60;
}
