#include "fightingtable2.h"
#include "ui_fightingtable2.h"

FightingTable2::FightingTable2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FightingTable2)
{
    ui->setupUi(this);

    ui->leftFlag->setPixmap(QPixmap(".\\resources\\images\\Canada.png"));
    ui->rightFlag->setPixmap(QPixmap(".\\resources\\images\\Switzerland.png"));

}

FightingTable2::~FightingTable2()
{
    delete ui;
}
