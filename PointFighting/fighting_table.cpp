#include "fighting_table.h"
#include <QMessageBox>
#include "ui_fighting_table.h"
#include "ui_form.h"
#include "formscore.h"
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <qmessagebox.h>



using namespace std::chrono;

FightingTable::FightingTable(QWidget *parent, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, int durationOfRound, int durationOfBreak, int countOfRounds, QImage leftFlag, QImage rightFlag, bool dialogForJudge, bool showAdvertisement) :
    QDialog(parent),
    ui(new Ui::FightingTable),
    nameLeft(nameLeft),
    nameRight(nameRight),

    durationOfRound(1000 * durationOfRound),
    durationOfBreak(1000 * durationOfBreak),
    countOfRounds(countOfRounds),

//    durationOfRound(1000 * 10),
//    durationOfBreak(1000 * 15),
//    countOfRounds(3),

    dialogForJudge(dialogForJudge),
    showAdvertisement(showAdvertisement)
{
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    ui->setupUi(this);

    if (!dialogForJudge){
        return;
    }

    left  << new FormScore(nameLeft , regionLeft , leftFlag , Qt::red );
    right << new FormScore(nameRight, regionRight, rightFlag, Qt::blue);

    ui->horizontalLayoutMain->addWidget(left .back());
    ui->horizontalLayoutMain->addWidget(right.back());

    allTables << this;

    for (int i = 0; i < QApplication::desktop()->screenCount(); ++i)
    {
        QRect screenres = QApplication::desktop()->screenGeometry(i);
        if (screenres == QApplication::desktop()->screenGeometry(-1))
            continue;
        FightingTable *tableForSpectators = new FightingTable(this, nameLeft, regionLeft, nameRight, regionRight, durationOfRound, durationOfBreak, countOfRounds, leftFlag, rightFlag, false, showAdvertisement);
        tableForSpectators->move(QPoint(screenres.x(), screenres.y()));
        tableForSpectators->resize(screenres.width(), screenres.height());
        tableForSpectators->showFullScreen();
        tableForSpectators->show();

        allTables << tableForSpectators;

        FormScore *a = new FormScore(nameRight, regionRight, rightFlag, Qt::blue);
        FormScore *b = new FormScore(nameLeft , regionLeft , leftFlag , Qt::red );
        left  << b;
        right << a;
        tableForSpectators->ui->horizontalLayoutMain->addWidget(a);
        tableForSpectators->ui->horizontalLayoutMain->addWidget(b);
    }

    pushButtonStart = new QPushButton();
    pushButtonStart->setText("Start");
    ui->widgetFooterHorizontalLayout->insertWidget(0, pushButtonStart);

    pushButtonDoctor = new QPushButton();
    pushButtonDoctor->setText("Call a doctor");
    ui->widgetFooterHorizontalLayout->insertWidget(1, pushButtonDoctor);

    currentRound = 1;
    countPointLeft = 0;
    countPointRight = 0;
    countOfLeftMinus = 0;
    countOfRightMinus = 0;
    countOfLeftFo = 0;
    countOfRightFo = 0;
    countOfLeftEx = 0;
    countOfRightEx = 0;

    status = Status::NotStart;
    ui->labelTime->setText(getTimeMMSS(this->durationOfRound));


    QTimer* timer = new QTimer(this);
    timer->start(poolTime);
    connect(timer, &QTimer::timeout, this, &FightingTable::update);




    countOfLeftMinus = 0;
    //connect(left[0]->ui->pushButtonPoint, &QPushButton::clicked, [this]{
        //ui->labelMinus->setPixmap(drawCubes(++countOfLeftMinus));
//        FormScore* form = dynamic_cast<FormScore*>(ui->horizontalLayoutMain->itemAt(0)->widget());
//        qDebug() << form->styleSheet();
//        if (rand() % 2)
//            form->setStyleSheet(form->styleSheet() + ";\nText-align:left");
//        else
//            form->setStyleSheet(form->styleSheet() + ";\nText-align:right");
//    });

    connect(pushButtonStart, &QPushButton::clicked, this, &FightingTable::on_pushButtonStart_clicked);
    connect(pushButtonDoctor, &QPushButton::clicked, this, &FightingTable::on_pushButtonDoctor_clicked);

    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonPointLeft_clicked );
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonPointRight_clicked);
    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, [this](){if (3 * countOfRightMinus < countPointLeft ) --countPointLeft;});
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, [this](){if (3 * countOfLeftMinus  < countPointRight) --countPointRight;});

    connect(left [0]->ui->pushButtonMinus, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonAddMinusLeft_clicked);
    connect(right[0]->ui->pushButtonMinus, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonAddMinusRight_clicked);
    connect(left [0]->ui->pushButtonMinus, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortMinusLeft_clicked);
    connect(right[0]->ui->pushButtonMinus, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortMinusRight_clicked);

    connect(left [0]->ui->pushButtonFo, &QRightClickButton::clicked,      [this](){ if (countOfLeftFo  == 0) countOfLeftFo  = 1;});
    connect(right[0]->ui->pushButtonFo, &QRightClickButton::clicked,      [this](){ if (countOfRightFo == 0) countOfRightFo = 1;});
    connect(left [0]->ui->pushButtonFo, &QRightClickButton::rightClicked, [this](){ if (countOfLeftFo  == 1) countOfLeftFo  = 0;});
    connect(right[0]->ui->pushButtonFo, &QRightClickButton::rightClicked, [this](){ if (countOfRightFo == 1) countOfRightFo = 0;});

    connect(left [0]->ui->pushButtonEx, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonAddExLeft_clicked);
    connect(right[0]->ui->pushButtonEx, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonAddExRight_clicked);
    connect(left [0]->ui->pushButtonEx, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortExLeft_clicked);
    connect(right[0]->ui->pushButtonEx, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortExRight_clicked);


//    countPointLeft =  1 + rand()%1000;
//    countPointRight = 1 + rand()%1000;
//    status = Status::Finish;
    showMaximized();
}

FightingTable::~FightingTable()
{
    delete ui;
    for (FightingTable* f : allTables)
        if (f != this)
            delete f;
}

QString FightingTable::getTimeMMSS(long long time)
{
    time /= 1000;
    return QString("%1").arg(time/60, 2, 10, QChar('0')) + ":" + QString("%1").arg(time%60, 2, 10, QChar('0'));
}





void FightingTable::update()
{
    long long curTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long quantum = curTime - prevTime;
    prevTime = curTime;
    //qDebug() << "quantum:" << quantum << status;

    if (status == Status::NotStart)
    {
        ui->labelLeftHead->setText(QString("Round 1/%1 - Not start").arg(countOfRounds));
    }
    else if (status == Status::Fighting)
    {
        spentTime += quantum;
        if (durationOfRound <= spentTime)
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
                spentTime = 0;
                status = Status::Break;
                if (showAdvertisement)
                    for (FightingTable* f : allTables)
                        if (f != this)
                            f->hide();
            }
            update();
        }
        else
        {
            for (FightingTable *f : allTables)
            {
                f->ui->labelLeftHead->setText(QString("Round %1/%2 - FIGHT!").arg(currentRound).arg(countOfRounds));
                f->ui->labelTime->setText(getTimeMMSS(durationOfRound - spentTime));
            }
        }
    }
    else if (status == Status::Break)
    {
        spentTime += quantum;
        if (durationOfBreak - spentTime <= 10 * 1000 && molot->isFinished()){
            molot->play();
            for (FightingTable* f : allTables)
                if (f != this && f->isHidden())
                    f->show();
        }
        if (durationOfBreak <= spentTime)
        {
            spentTime = 0;
            ++currentRound;
            status = Status::Fighting;
            molot->stop();
            gong->play();
            update();
        }
        else
        {
            for (FightingTable *f : allTables)
            {
                f->ui->labelLeftHead->setText(QString("Round %1/%2 - Break").arg(currentRound).arg(countOfRounds));
                f->ui->labelTime->setText(getTimeMMSS(durationOfBreak - spentTime));
            }
        }
    }
    else if (status == Status::Pause)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText(QString("Round %1/%2 - Fight! - PAUSE").arg(currentRound).arg(countOfRounds));
    }
    else if (status == Status::DoctorOnRing)
    {
        spentTimeDoctor += quantum;
        long long x = durationOfDoctorOnRing - spentTimeDoctor;
        if (0 < x)
        {
            for (FightingTable *f : allTables)
                f->ui->labelDoctorTimer->setText("Doctor: " + getTimeMMSS(x));
        }
        else
        {
            on_pushButtonDoctor_clicked();
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
            for (FightingTable *f : allTables)
            {
                f->ui->labelLeftHead->setText("Tie...");
                f->ui->labelTime->setText("00:00");
            }
            for (FormScore *f : left ) f->setWinner(true);
            for (FormScore *f : right) f->setWinner(true);
        }
    }
    else if (status == Status::Finish)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");

            QPalette palette = f->ui->labelTime->palette();
            palette.setColor(f->ui->labelTime->backgroundRole(), QColor(255, 255, 0));
            palette.setColor(f->ui->labelTime->foregroundRole(), QColor(255, 255, 0));
            f->ui->labelTime->setPalette(palette);
            f->ui->labelTime->setText(QString("Winner is ") + (countPointLeft > countPointRight? nameLeft : nameRight));
        }
        if (countPointLeft > countPointRight)
        {
            for (FormScore *f : left ) f->setWinner(true);
            for (FormScore *f : right) f->setWinner(false);
        }
        else if (countPointLeft < countPointRight)
        {
            for (FormScore *f : left ) f->setWinner(false);
            for (FormScore *f : right) f->setWinner(true);
        }
        else
            status = Status::Tie;
    }
    else if (status == Status::DisqualificationLeft)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
        for (FormScore *f : left ) f->setWinner(false);
        for (FormScore *f : right) f->setWinner(true);
    }
    else if (status == Status::DisqualificationRight)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
        for (FormScore *f : left ) f->setWinner(true);
        for (FormScore *f : right) f->setWinner(false);
    }

    for (FightingTable *f : allTables)
        f->ui->labelRightHead->setText(ui->labelLeftHead->text());


    for (FormScore *f : left ) {
        f->ui->pushButtonPoint->setText(QString::number(countPointLeft ));
        f->setCountMinus(countOfLeftMinus);
        f->setCountFo(countOfLeftFo);
        f->setCountEx(countOfLeftEx);
    }
    for (FormScore *f : right)
    {
        f->ui->pushButtonPoint->setText(QString::number(countPointRight));
        f->setCountMinus(countOfRightMinus);
        f->setCountFo(countOfRightFo);
        f->setCountEx(countOfRightEx);
    }
}


void FightingTable::on_pushButtonStart_clicked()
{
    if (status == Status::NotStart)
    {
        spentTime = 0;
        currentRound = 1;
        status = Status::Fighting;
        countPointLeft = 0;
        countPointRight = 0;
        pushButtonStart->setText("Pause");
        gong->play();
        update();
    }
    else if (status == Status::Fighting)
    {
        status = Status::Pause;
        pushButtonStart->setText("Continue");
        update();
    }
    else if (status == Status::Pause)
    {
        status = Status::Fighting;

        pushButtonStart->setText("Pause");
        update();
    }
}

void FightingTable::on_pushButtonPointLeft_clicked()
{
    if (status != Status::NotStart)
    {
        ++countPointLeft;
    }
}

void FightingTable::on_pushButtonPointRight_clicked()
{
    if (status != Status::NotStart)
    {
        ++countPointRight;
    }
}

void FightingTable::on_pushButtonAddMinusLeft_clicked()
{
    if (status == Status::NotStart || status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return;
    ++countOfLeftMinus;
    if (1 <= countPointLeft)
    {
        --countPointLeft;
        stackMinusLeft << true;
    }
    else
    {
        ++countPointRight;
        stackMinusLeft << false;
    }
    if (countOfLeftMinus == 3)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationLeft;
    }
}

void FightingTable::on_pushButtonAddMinusRight_clicked()
{
    if (status == Status::NotStart || status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return;
    ++countOfRightMinus;
    if (1 <= countPointRight)
    {
        --countPointRight;
        stackMinusRight << true;
    }
    else
    {
        ++countPointLeft;
        stackMinusRight << false;
    }
    if (countOfRightMinus == 3)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationRight;
    }
}

void FightingTable::on_pushButtonAbortMinusLeft_clicked()
{
    //if (countOfLeftMinus == 0 || countOfLeftMinus == countOfLeftEx - 1)
    if (stackMinusLeft.empty())
        return;
    --countOfLeftMinus;
    if (stackMinusLeft.pop())
        ++countPointLeft;
    else
        --countPointRight;
    if ((status == Status::DisqualificationLeft || status == Status::DisqualificationRight) && countOfLeftMinus <= 3 && countOfRightMinus <= 3)
    {
        status = statusBeforDisqualification;
        for (FormScore *f : left ) f->setWinner(true);
        for (FormScore *f : right) f->setWinner(true);
    }
}

void FightingTable::on_pushButtonAbortMinusRight_clicked()
{
    if (countOfRightMinus == 0 || countOfRightMinus == countOfRightEx - 1)
        return;
    --countOfRightMinus;
    if (stackMinusRight.pop())
        ++countPointRight;
    else
        --countPointLeft;
    if ((status == Status::DisqualificationLeft || status == Status::DisqualificationRight) && countOfLeftMinus <= 3 && countOfRightMinus <= 3)
    {
        status = statusBeforDisqualification;
        for (FormScore *f : left ) f->setWinner(true);
        for (FormScore *f : right) f->setWinner(true);
    }
}

void FightingTable::on_pushButtonAddExLeft_clicked()
{
    if (status == Status::NotStart || status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return;
    ++countOfLeftEx;
    if (2 <= countOfLeftEx)
    {
        if (1 <= countPointLeft)
        {
            --countPointLeft;
            stackLeftEx << true;
        }
        else
        {
            ++countPointRight;
            stackLeftEx << false;
        }
    }
    if (countOfLeftEx == 4)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationLeft;
    }
}

void FightingTable::on_pushButtonAddExRight_clicked()
{
    if (status == Status::NotStart || status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return;
    ++countOfRightEx;
    if (2 <= countOfRightEx)
    {
        if (1 <= countPointRight)
        {
            --countPointRight;
            stackRightEx << true;
        }
        else
        {
            ++countPointLeft;
            stackRightEx << false;
        }
    }
    if (countOfRightEx == 4)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationLeft;
    }
}

void FightingTable::on_pushButtonAbortExLeft_clicked()
{
    if (!countOfLeftEx)
        return;
    --countOfLeftEx;
    if (1 <= countOfLeftEx)
    {
        if (stackLeftEx.pop())
            ++countPointLeft;
        else
            --countPointRight;
    }
    if ((status == Status::DisqualificationLeft || status == Status::DisqualificationRight) && countOfLeftEx <= 3 && countOfRightEx <= 3)
    {
        status = statusBeforDisqualification;
        for (FormScore *f : left ) f->setWinner(true);
        for (FormScore *f : right) f->setWinner(true);
    }
}

void FightingTable::on_pushButtonAbortExRight_clicked()
{
    if (!countOfRightEx)
        return;
    --countOfRightEx;
    if (1 <= countOfRightEx)
    {
        if (stackRightEx.pop())
            ++countPointRight;
        else
            --countPointLeft;
    }
    if ((status == Status::DisqualificationLeft || status == Status::DisqualificationRight) && countOfLeftEx <= 3 && countOfRightEx <= 3)
    {
        status = statusBeforDisqualification;
        for (FormScore *f : left ) f->setWinner(true);
        for (FormScore *f : right) f->setWinner(true);
    }
}


void FightingTable::on_pushButtonDoctor_clicked()
{
    if (status == Status::DoctorOnRing)
    {        
        status = Status::Fighting;
        update();
        for (FightingTable *f : allTables)
            f->ui->labelDoctorTimer->setText("");
        pushButtonDoctor->setText("Call a doctor");
    }
    else if (status == Status::Fighting)
    {
        status = Status::DoctorOnRing;
        spentTimeDoctor = 0;
        pushButtonDoctor->setText("Stop a doctor");
        update();
        qDebug() << "Doc on the ring";
    }
}

QString FightingTable::getResult()
{
    if (status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return "DISQ";
    return QString::number(countPointLeft) + " : " + QString::number(countPointRight);
}

FightingTable::Player FightingTable::getWinner()
{
    if (status == Status::DisqualificationRight || status == Status::Finish && countPointLeft > countPointRight) return Player::LeftPlayer;
    if (status == Status::DisqualificationLeft  || status == Status::Finish && countPointLeft < countPointRight) return Player::RightPlayer;
    return Player::NoPlayer;
}
