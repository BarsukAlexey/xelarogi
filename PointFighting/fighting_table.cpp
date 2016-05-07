#include "fighting_table.h"
#include <QMessageBox>
#include "ui_fighting_table.h"
#include "ui_form.h"
#include "dialogdisq.h"
#include "formscore.h"
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <qmessagebox.h>



using namespace std::chrono;

FightingTable::FightingTable(QWidget *parent, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, int durationOfRound, int durationOfBreak, int countOfRounds, QImage leftFlag, QImage rightFlag, bool dialogForJudge, bool showAdvertisement, int timeExtraRound) :
    QDialog(parent),
    ui(new Ui::FightingTable),
    nameLeft(nameLeft),
    nameRight(nameRight),

    durationOfDoctorOnRing(2 * 60 * 1000),
    durationOfRound(1000 * durationOfRound),
    durationOfBreak(1000 * durationOfBreak),
    countOfRounds(countOfRounds),
    durationExtraRound(1000 * timeExtraRound),

//    durationOfDoctorOnRing(5 * 1000),
//    durationOfRound(1000 * 2),
//    durationOfBreak(1000 * 15),
//    countOfRounds(1),
//    durationExtraRound(0 * 1000),


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
        FightingTable *tableForSpectators = new FightingTable(this, nameLeft, regionLeft, nameRight, regionRight, durationOfRound, durationOfBreak, countOfRounds, leftFlag, rightFlag, false, showAdvertisement, durationExtraRound);
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

    pushButtonStop = new QPushButton();
    pushButtonStop->setText("Stop round");
    ui->widgetFooterHorizontalLayout->insertWidget(2, pushButtonStop);

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

    connect(pushButtonStart, &QPushButton::clicked, this, &FightingTable::on_pushButtonStart_clicked);
    connect(pushButtonDoctor, &QPushButton::clicked, this, &FightingTable::on_pushButtonDoctor_clicked);
    connect(pushButtonStop, &QPushButton::clicked, [this](){
        Status statusBefor = status;
        status = Status::stopedByJudge;
        DialogDisq dlg;
        if (dlg.exec() == QDialog::Accepted)
        {
            if (dlg.getWinner() == Player::LeftPlayer)
                status = Status::forceLeftWinner;
            else
                status = Status::forceRightWinner;
            forceResult = dlg.getResult();
        }
        else
        {
            status = statusBefor;
        }
    });

    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonPointLeft_clicked );
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::clicked, this, &FightingTable::on_pushButtonPointRight_clicked);
    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortPointLeft_clicked);
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, this, &FightingTable::on_pushButtonAbortPointRight_clicked);

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

    showMaximized();


//    countPointLeft =  1 + rand()%1000;
//    countPointRight = 1 + rand()%1000;
//    status = Status::Finish;
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
    //return;
    qDebug() << status << Status::ExtraRound << Status::DoctorOnRing;


    long long curTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long quantum = curTime - prevTime;
    prevTime = curTime;
//    qDebug() << "quantum:" << quantum << status;

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
                {
                    if (durationExtraRound == 0)
                        status = Status::Tie;
                    else
                        status = Status::PendingExtraRound;
                }
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
            gong->play();
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
    else if (status == Status::PauseExtraRound)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("Extra round - Fight! - PAUSE");
    }
    else if (status == Status::PendingExtraRound)
    {
        pushButtonStart->setText("Start extra round!");
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("Extra round - Not start");
            f->ui->labelTime->setText(getTimeMMSS(durationExtraRound));
        }
        spentTime = 0;
    }
    else if (status == Status::ExtraRound)
    {
        spentTime += quantum;
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("Extra round - Fight!");
            f->ui->labelTime->setText(getTimeMMSS(qMax(durationExtraRound - spentTime, 0LL)));
        }
        if (durationExtraRound < spentTime && countPointLeft != countPointRight)
        {
            status = Status::Finish;
            gong->play();
        }
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
        }
    }
    else if (status == Status::Finish)
    {
        if (countPointLeft == countPointRight)
            status = Status::Tie;
        else
        {
            for (FightingTable *f : allTables)
            {
                f->ui->labelLeftHead->setText("");
                f->ui->labelTime->setText(QString("Winner is ") + (countPointLeft > countPointRight? nameLeft : nameRight));
            }
        }
    }
    else if (status == Status::DisqualificationLeft)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
    }
    else if (status == Status::DisqualificationRight)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
    }
    else if (status == winnerByPointsLeft)
    {
    }
    else if (status == winnerByPointsRight)
    {
    }


    for (FightingTable *f : allTables)
        f->ui->labelRightHead->setText(ui->labelLeftHead->text());

    for (FormScore *f : left )
    {
        f->ui->pushButtonPoint->setText(QString::number(countPointLeft ));
        f->setCountMinus(countOfLeftMinus);
        f->setCountFo(countOfLeftFo);
        f->setCountEx(countOfLeftEx);
        f->setWinner(getWinner() != Player::RightPlayer);  // true if non or left
    }
    for (FormScore *f : right)
    {
        f->ui->pushButtonPoint->setText(QString::number(countPointRight));
        f->setCountMinus(countOfRightMinus);
        f->setCountFo(countOfRightFo);
        f->setCountEx(countOfRightEx);
        f->setWinner(getWinner() != Player::LeftPlayer); // true if non or right
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
    else if (status == Status::PendingExtraRound)
    {
        status = Status::ExtraRound;
        pushButtonStart->setText("Pause");
        gong->play();
    }
    else if (status == Status::ExtraRound)
    {
        status = Status::PauseExtraRound;
        pushButtonStart->setText("Continuse");
    }
    else if (status == Status::PauseExtraRound)
    {
        status = Status::ExtraRound;
        pushButtonStart->setText("Pause");
    }
}

void FightingTable::on_pushButtonPointLeft_clicked()
{
    if (getWinner() != Player::NoPlayer) return;

    ++countPointLeft;
    if (countPointRight + 10 <= countPointLeft)
    {
        statusBeforDisqualification = status;
        status = Status::winnerByPointsLeft;
    }
}

void FightingTable::on_pushButtonPointRight_clicked()
{
    if (getWinner() != Player::NoPlayer) return;

    ++countPointRight;
    if (countPointLeft + 10 <= countPointRight)
    {
        statusBeforDisqualification = status;
        status = Status::winnerByPointsRight;
    }
}

void FightingTable::on_pushButtonAbortPointLeft_clicked()
{
    int sub = 0;
    for (std::pair<int, int> p : stackMinusLeft ) sub += p.first;
    for (std::pair<int, int> p : stackMinusRight) sub += p.first;
    for (std::pair<int, int> p : stackLeftEx    ) sub += p.first;
    for (std::pair<int, int> p : stackRightEx   ) sub += p.first;

    if (0 <= countPointLeft - sub - 1)
    {
        --countPointLeft;
        if (status == Status::winnerByPointsLeft)
            status = statusBeforDisqualification;
    }
}

void FightingTable::on_pushButtonAbortPointRight_clicked()
{

    int sub = 0;
    for (std::pair<int, int> p : stackMinusLeft ) sub += p.second;
    for (std::pair<int, int> p : stackMinusRight) sub += p.second;
    for (std::pair<int, int> p : stackLeftEx    ) sub += p.second;
    for (std::pair<int, int> p : stackRightEx   ) sub += p.second;
    if (0 <= countPointRight - sub - 1)
    {
        --countPointRight;
        if (status == Status::winnerByPointsRight)
            status = statusBeforDisqualification;
    }
}

void FightingTable::on_pushButtonAddMinusLeft_clicked()
{
    if (getWinner() != Player::NoPlayer) return;

    ++countOfLeftMinus;
    if (1 <= countPointLeft)
    {
        --countPointLeft;
        stackMinusLeft << std::make_pair(-1, 0);
    }
    else
    {
        ++countPointRight;
        stackMinusLeft << std::make_pair(0, 1);
    }
    if (countOfLeftMinus == 3)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationLeft;
    }
}

void FightingTable::on_pushButtonAddMinusRight_clicked()
{
    if (getWinner() != Player::NoPlayer) return;

    ++countOfRightMinus;
    if (1 <= countPointRight)
    {
        --countPointRight;
        stackMinusRight << std::make_pair(0, -1);
    }
    else
    {
        ++countPointLeft;
        stackMinusRight << std::make_pair(1, 0);
    }
    if (countOfRightMinus == 3)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationRight;
    }
}

void FightingTable::on_pushButtonAbortMinusLeft_clicked()
{
    if (stackMinusLeft.empty())
        return;
    --countOfLeftMinus;
    std::pair<int, int> pop = stackMinusLeft.pop();
    countPointLeft  -= pop.first;
    countPointRight -= pop.second;
    if (status == Status::DisqualificationLeft && countOfLeftMinus <= 2)
    {
        status = statusBeforDisqualification;
    }
}

void FightingTable::on_pushButtonAbortMinusRight_clicked()
{
    if (stackMinusRight.empty())
        return;
    --countOfRightMinus;
    std::pair<int, int> pop = stackMinusRight.pop();
    countPointLeft  -= pop.first;
    countPointRight -= pop.second;
    if (status == Status::DisqualificationRight && countOfRightMinus <= 2)
    {
        status = statusBeforDisqualification;
    }
}

void FightingTable::on_pushButtonAddExLeft_clicked()
{
    if (getWinner() != Player::NoPlayer) return;

    ++countOfLeftEx;
    if (2 <= countOfLeftEx)
    {
        if (1 <= countPointLeft)
        {
            --countPointLeft;
            stackLeftEx << std::make_pair(-1, 0);
        }
        else
        {
            ++countPointRight;
            stackLeftEx <<  std::make_pair(0, 1);
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
    if (getWinner() != Player::NoPlayer) return;

    ++countOfRightEx;
    if (2 <= countOfRightEx)
    {
        if (1 <= countPointRight)
        {
            --countPointRight;
            stackRightEx <<  std::make_pair(0, -1);
        }
        else
        {
            ++countPointLeft;
            stackRightEx <<  std::make_pair(1, 0);
        }
    }
    if (countOfRightEx == 4)
    {
        statusBeforDisqualification = status;
        status = Status::DisqualificationRight;
    }
}

void FightingTable::on_pushButtonAbortExLeft_clicked()
{
    if (!countOfLeftEx)
        return;
    --countOfLeftEx;
    if (1 <= countOfLeftEx)
    {
        std::pair<int, int> pop = stackLeftEx.pop();
        countPointLeft  -= pop.first;
        countPointRight -= pop.second;
    }
    if (status == Status::DisqualificationLeft && countOfRightEx <= 3)
    {
        status = statusBeforDisqualification;
    }
}

void FightingTable::on_pushButtonAbortExRight_clicked()
{
    if (!countOfRightEx)
        return;
    --countOfRightEx;
    if (1 <= countOfRightEx)
    {
        std::pair<int, int> pop = stackRightEx.pop();
        countPointLeft  -= pop.first;
        countPointRight -= pop.second;
    }
    if (status == Status::DisqualificationRight && countOfRightEx <= 3)
    {
        status = statusBeforDisqualification;
    }
}


void FightingTable::on_pushButtonDoctor_clicked()
{
    if (status == Status::DoctorOnRing)
    {        
        status = statusBeforDisqualification;
        for (FightingTable *f : allTables)
            f->ui->labelDoctorTimer->setText("");
        pushButtonDoctor->setText("Call a doctor");
    }
    else if (status == Status::Fighting || status == Status::ExtraRound)
    {
        statusBeforDisqualification = status;
        status = Status::DoctorOnRing;
        spentTimeDoctor = 0;
        pushButtonDoctor->setText("Stop a doctor");
    }
}

QString FightingTable::getResult()
{
    if (status == Status::DisqualificationLeft || status == Status::DisqualificationRight)
        return "DISQ";
    if (status == Status::forceLeftWinner || status == Status::forceRightWinner)
        return forceResult;

    return QString::number(countPointLeft) + " : " + QString::number(countPointRight);
}

FightingTable::Player FightingTable::getWinner()
{
    if (status == Status::forceLeftWinner  || status == Status::winnerByPointsLeft  || status == Status::DisqualificationRight || status == Status::Finish && countPointLeft > countPointRight) return Player::LeftPlayer;
    if (status == Status::forceRightWinner || status == Status::winnerByPointsRight || status == Status::DisqualificationLeft  || status == Status::Finish && countPointLeft < countPointRight) return Player::RightPlayer;
    return Player::NoPlayer;
}
