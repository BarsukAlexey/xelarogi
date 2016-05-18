#include "dialogdisq.h"
#include "ui_dialogdisq.h"

DialogDisq::DialogDisq(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDisq)
{
    ui->setupUi(this);

    connect(this, &DialogDisq::accepted, [this](){});
    connect(this, &DialogDisq::rejected, [this](){});
}

DialogDisq::~DialogDisq()
{
    delete ui;
}

Fighting::Player DialogDisq::getWinner()
{
    if (ui->radioButton_Left->isChecked())
        return Fighting::Player::Left;
    return Fighting::Player::Right;
}

QString DialogDisq::getResult()
{
    return ui->lineEdit->text();
}
