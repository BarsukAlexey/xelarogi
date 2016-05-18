#include "fighting_table.h"

FightingTable::FightingTable(Fighting* f, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, QImage leftFlag, QImage rightFlag, bool dialogForJudge, bool showAdvertisement) :
    QDialog(),
    f(f),
    ui(new Ui::FightingTable),
    nameLeft(nameLeft),

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
        FightingTable *tableForSpectators = new FightingTable(f, nameLeft, regionLeft, nameRight, regionRight, leftFlag, rightFlag, false, showAdvertisement);
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


    ui->labelTime->setText(getTimeMMSS(f->getDurationOfRound()));


    QTimer* timer = new QTimer(this);
    timer->start(poolTime);
    connect(timer, &QTimer::timeout, this, &FightingTable::updateInfo);

    connect(pushButtonStart, &QPushButton::clicked, [f](){f->pressedKeySpace();});
    connect(pushButtonDoctor, &QPushButton::clicked, [f](){f->pressDoctor();});
    connect(pushButtonStop, &QPushButton::clicked, [this, f](){
        f->setDialog(true);
        DialogDisq dlg;
        if (dlg.exec() == QDialog::Accepted)
        {
            f->forceStopRound(dlg.getWinner(), dlg.getResult());
        }
        else
        {
            f->setDialog(false);
        }
    });

    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::clicked, [f](){f->addOnePointToLeftFighter();} );
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::clicked, [f](){f->addOnePointToRightFighter();});
    connect(left [0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, [f](){f->cancelLeftPoint();});
    connect(right[0]->ui->pushButtonPoint, &QRightClickButton::rightClicked, [f](){f->cancelRightPoint();});

    connect(left [0]->ui->pushButtonMinus, &QRightClickButton::clicked, [f](){f->addMinusToLeft();});
    connect(right[0]->ui->pushButtonMinus, &QRightClickButton::clicked, [f](){f->addMinusToRight();});

    connect(left [0]->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToRight(); });
    connect(right[0]->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToRight(); });

    connect(left [0]->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToLeft();});
    connect(right[0]->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToRight();});

    showMaximized();


    //    countPointLeft =  1 + rand()%1000;
    //    countPointRight = 1 + rand()%1000;
    //    status = Status::Finish;
}

QString FightingTable::getTimeMMSS(long long time)
{
    time /= 1000;
    return QString("%1").arg(time/60, 2, 10, QChar('0')) + ":" + QString("%1").arg(time%60, 2, 10, QChar('0'));
}





void FightingTable::updateInfo()
{
    //return;
    Fighting::FightStatus fightStatus = f->getStatus();


    if (fightStatus == Fighting::NotStart)
    {
        ui->labelLeftHead->setText(QString("Round 1/%1 - Not start").arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::Fight)
    {
        for (FightingTable *ft : allTables)
        {
            //            ft->ui->labelLeftHead->setText(QString("Round %1/%2 - FIGHT!").arg(f->getCurrentRound()).arg(f->getCountOfRounds));
            ft->ui->labelTime->setText(f->getStringTime());
        }
    }

    /*/
    else if (fightStatus == Fighting::Break)
    {
    if (showAdvertisement)
        for (FightingTable* f : allTables)
            if (f != this)
                f->hide();

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
            fightStatus = Fighting::Fighting;
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
    else if (fightStatus == Fighting::Pause)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText(QString("Round %1/%2 - Fight! - PAUSE").arg(currentRound).arg(countOfRounds));
    }
    else if (fightStatus == Fighting::PauseExtraRound)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("Extra round - Fight! - PAUSE");
    }
    else if (fightStatus == Fighting::PendingExtraRound)
    {
        pushButtonStart->setText("Start extra round!");
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("Extra round - Not start");
            f->ui->labelTime->setText(getTimeMMSS(durationExtraRound));
        }
        spentTime = 0;
    }
    else if (fightStatus == Fighting::ExtraRound)
    {
        spentTime += quantum;
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("Extra round - Fight!");
            f->ui->labelTime->setText(getTimeMMSS(qMax(durationExtraRound - spentTime, 0LL)));
        }
        if (durationExtraRound < spentTime && countPointLeft != countPointRight)
        {
            if (countPointLeft > countPointRight)
                fightStatus = Fighting::winnerByPointsLeft;
            else
                fightStatus = Fighting::winnerByPointsRight;
            gong->play();
        }
    }
    else if (fightStatus == Fighting::DoctorOnRing)
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
    else if (fightStatus == Fighting::Tie)
    {
        if (countPointLeft != countPointRight)
        {
            if (countPointLeft > countPointRight)
                fightStatus = Fighting::winnerByPointsLeft;
            else
                fightStatus = Fighting::winnerByPointsRight;
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
    else if (fightStatus == Fighting::DisqualificationLeft)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
    }
    else if (fightStatus == Fighting::DisqualificationRight)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText("Disqualification");
        }
    }
    else if (fightStatus == winnerByPointsLeft)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText(QString("Winner is ") + nameLeft);
        }
    }
    else if (fightStatus == winnerByPointsRight)
    {
        for (FightingTable *f : allTables)
        {
            f->ui->labelLeftHead->setText("");
            f->ui->labelTime->setText(QString("Winner is ") + nameRight);
        }
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
    /**/
}

void FightingTable::closeEvent(QCloseEvent* event)
{
    if (dialogForJudge)
    {
        if (f->getStatus() == Fighting::FightStatus::NotStart || f->getWinner() != Fighting::Player::NoPlayer)
        {
            event->accept(); // close window
            for (FightingTable* f : allTables)
                f->hide();
        }
        else
        {
            event->ignore(); // keep window
            QMessageBox::warning(this, "", "Contest is not finished.\nDon't close this window!");
        }
    }
    else
    {
        event->ignore(); // keep window
    }
}
