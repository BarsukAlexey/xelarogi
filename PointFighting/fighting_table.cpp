
#include "fighting_table.h"
#include "ui_fighting_table.h"


FightingTable::FightingTable(Fighting* f, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, QImage leftFlag, QImage rightFlag, bool dialogForJudge, bool showAdvertisement) :
    QDialog(),
    f(f),
    ui(new Ui::FightingTable),
    nameLeft(nameLeft),
    nameRight(nameRight),
    mLeftFlag(leftFlag),
    mRightFlag(rightFlag),
    dialogForJudge(dialogForJudge),
    showAdvertisement(showAdvertisement)
{
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    ui->setupUi(this);

    connect(f, SIGNAL(statusOrPointsChanged()), this, SLOT(updateInfo()));

    if (!dialogForJudge){
        return;
    }

    left  << new FormScore(nameLeft , regionLeft , leftFlag , Qt::red );
    right << new FormScore(nameRight, regionRight, rightFlag, Qt::blue);

    ui->horizontalLayoutMain->addWidget(left .back(), 50);
    ui->horizontalLayoutMain->addWidget(right.back(), 50);


    allTables << this;
    //

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

    cancelLastPenalty = new QPushButton();
    cancelLastPenalty->setText("Cancel Last Penalty");
    ui->widgetFooterHorizontalLayout->insertWidget(2, cancelLastPenalty);

    pushButtonStop = new QPushButton();
    pushButtonStop->setText("Stop round");
    ui->widgetFooterHorizontalLayout->insertWidget(3, pushButtonStop);

    connect(pushButtonStart, &QPushButton::clicked, [f](){f->pressedKeySpace();});
    connect(pushButtonDoctor, &QPushButton::clicked, [f](){f->pressDoctor();});
    connect(cancelLastPenalty, &QPushButton::clicked, [f](){f->cancelLastAction();});
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

    connect(left [0]->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToLeft(); });
    connect(right[0]->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToRight(); });

    connect(left [0]->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToLeft();});
    connect(right[0]->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToRight();});

    showMaximized();
    updateInfo();
}

FightingTable::~FightingTable(){
    delete ui;
    for (FightingTable* f : allTables)
        if (f != this)
            delete f;
}



void FightingTable::updateInfo()
{

    //qDebug() << __PRETTY_FUNCTION__ << f->statusName[f->getStatus()];
    //return;
    Fighting::FightStatus fightStatus = f->getStatus();



    if (fightStatus != Fighting::DoctorOnRing)
        for (FightingTable *ft : allTables)
            ft->ui->labelDoctorTimer->setText("");
    else
        for (FightingTable *ft : allTables)
            ft->ui->labelDoctorTimer->setText("Doctor: " + f->getStringTimeDoctor());



    if (f->getWinner() == Fighting::Player::NoPlayer)
        for (FightingTable *ft : allTables)
            ft->ui->labelTime->setText(f->getStringTime());
    else
        for (FightingTable *ft : allTables)
        {
            if (dialogForJudge)
                ft->ui->labelTime->setText(QString("Winner is ") + (f->getWinner() == Fighting::Player::Left? nameLeft : nameRight) + " (" + f->getResult() + ")");
            else
                ft->ui->labelTime->setText(QString("Winner is ") + (f->getWinner() == Fighting::Player::Left? nameLeft : nameRight));
        }



    if (dialogForJudge)
    {
        if (fightStatus == Fighting::PendingExtraRound)
            pushButtonStart->setText("Start extra round!");
        else if (fightStatus == Fighting::NotStart)
            pushButtonStart->setText("Start!");
        else
            pushButtonStart->setText("Pause");



        if (fightStatus == Fighting::DoctorOnRing)
            pushButtonDoctor->setText("Stop a doctor");
        else
            pushButtonDoctor->setText("Call a doctor");
    }



    if (fightStatus == Fighting::NotStart)
    {
        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText(QString("Round 1/%1 - Not start").arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::Fight)
    {
        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText(QString("Round %1/%2 - FIGHT!").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::Break)
    {
        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText(QString("Round %1/%2 - Break").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));

        if (showAdvertisement)
        {
            if (10 * 1000 < f->getTimeMS())
            {
                for (FightingTable* f : allTables)
                    if (f != this && !f->isHidden())
                        f->hide();
            }
            else
            {
                for (FightingTable* f : allTables)
                    if (f != this && f->isHidden())
                        f->show();
            }
        }
    }
    else if (fightStatus == Fighting::PauseFight)
    {
        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText(QString("Round %1/%2 - Fight! - PAUSE").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::DoctorOnRing)
    {
    }
    else if (fightStatus == Fighting::Tie)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("Tie...");
    }
    else if (fightStatus == Fighting::DisqualificationLeft)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::DisqualificationRight)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsLeft)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsRight)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsLeft10)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsRight10)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::stoppedByJudge)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::forceLeftWinner)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::forceRightWinner)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::PendingExtraRound)
    {
        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText("Extra round - Not start");
    }
    else if (fightStatus == Fighting::ExtraRound)
    {

        for (FightingTable *ft : allTables)
            ft->ui->labelLeftHead->setText("Extra round - Fight!");
    }
    else if (fightStatus == Fighting::PauseExtraRound)
    {
        for (FightingTable *f : allTables)
            f->ui->labelLeftHead->setText("Extra round - Fight! - PAUSE");
    }



    for (FightingTable *f : allTables)
        f->ui->labelRightHead->setText(ui->labelLeftHead->text());

    for (FormScore *fs : left )
    {
        fs->ui->pushButtonPoint->setText(QString::number(f->getCountOfPointsForLeftFighter()));
        fs->setCountMinus(f->getCountOfMinusToLeft());
        fs->setCountFo(f->getCountOfForestallingToLeft());
        fs->setCountEx(f->getCountOfExToLeft());
        fs->setWinner(f->getWinner() != Fighting::Player::Right);  // true if non or left
    }
    for (FormScore *fs : right)
    {
        fs->ui->pushButtonPoint->setText(QString::number(f->getCountOfPointsForRightFighter()));
        fs->setCountMinus(f->getCountOfMinusToRight());
        fs->setCountFo(f->getCountOfForestallingToRight());
        fs->setCountEx(f->getCountOfExToRight());
        fs->setWinner(f->getWinner() != Fighting::Player::Left); // true if non or right
    }
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
