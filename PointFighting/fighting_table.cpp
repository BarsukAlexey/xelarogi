#include "fighting_table.h"
#include "ui_fighting_table.h"

#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <chrono>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
using namespace std::chrono;

FightingTable::FightingTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FightingTable)
{
    ui->setupUi(this);
    status = Status::NotStart;

    QTimer* timer = new QTimer(this);
    timer->start(poolTime);
    connect(timer, &QTimer::timeout, this, &FightingTable::update);
}

FightingTable::~FightingTable()
{
    delete ui;
}



void FightingTable::update()
{
    long long curTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long time = (curTime - startTime - sumOfDelay) / 1000;
    if (status == Status::NotStart)
    {
        ui->labelLeftHead->setText("Not start");
    }
    else if (status == Status::Fighting)
    {
        if (durationOfRound <= time)
        {
            if (currentRound == countOfRounds)
            {
                if (countPointLeft == countPointRight)
                    status = Status::Tie;
                else
                    status = Status::Finish;
            }
            else
            {
                startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                status = Status::Break;
            }
            update();
        }
        else
        {
            ui->labelLeftHead->setText("Fight!");
            ui->labelTime->setText(QString("%1").arg((durationOfRound-time)/60, 2, 10, QChar('0')) + ":" + QString("%1").arg((durationOfRound-time)%60, 2, 10, QChar('0')));
        }
    }
    else if (status == Status::Break)
    {
        if (durationOfBreak <= time)
        {
            startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            ++currentRound;
            status = Status::Fighting;
            update();
        }
        else
        {
            ui->labelLeftHead->setText("Break");
            ui->labelTime->setText(QString("%1").arg((durationOfBreak-time)/60, 2, 10, QChar('0')) + ":" + QString("%1").arg((durationOfBreak-time)%60, 2, 10, QChar('0')));
        }
    }
    else if (status == Status::Tie)
    {
        if (countPointLeft != countPointRight)
        {
            status = Status::Finish;
            update();
        }
        else
        {
            ui->labelLeftHead->setText("Tie...");
            ui->labelTime->setText("00:00");
        }
    }
    else if (status == Status::Finish)
    {
        ui->labelLeftHead->setText(QString("Winner is ") + (countPointLeft < countPointRight? " ПРАВЫЙ!" : "ЛЕВЫЙ"));
        ui->labelTime->setText("00:00");
    }
    ui->labelRightHead->setText(ui->labelLeftHead->text());
}


void FightingTable::on_pushButtonStart_clicked()
{
    startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    sumOfDelay = 0;
    currentRound = 1;
    status = Status::Fighting;
    countPointLeft = 0;
    countPointRight = 0;

    ui->pushButtonStart->setEnabled(false);
}

void FightingTable::on_pushButtonPointLeft_clicked()
{
    if (status == Status::Fighting || status == Status::Tie)
    {
        ++countPointLeft;
        ui->pushButtonPointLeft->setText(QString::number(countPointLeft));
        update();
    }
}

void FightingTable::on_pushButtonPointRight_clicked()
{
    if (status == Status::Fighting || status == Status::Tie)
    {
        ++countPointRight;
        ui->pushButtonPointRight->setText(QString::number(countPointRight));
        update();
    }
}
