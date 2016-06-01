#include "fightingtable2.h"
#include "ui_fightingtable2.h"

FightingTable2::FightingTable2(Fighting* f, QString categoty, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, QImage leftFlag, QImage rightFlag, bool isForJudge, bool showAdvertisement, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FightingTable2),
    f(f),
    isForJudge(isForJudge),
    showAdvertisement(showAdvertisement)
{
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    ui->setupUi(this);

    ui->labelTime->setLableAsTimer(true);

    ui->labelCategory->setText(categoty);

    ui->leftName ->setText(isForJudge? nameLeft  : nameRight);
    ui->rightName->setText(isForJudge? nameRight : nameLeft );

    ui->leftRegion ->setText(isForJudge? regionLeft  : regionRight);
    ui->rightRegion->setText(isForJudge? regionRight : regionLeft );

    ui->leftFlag ->setPixmap(isForJudge? FormScore::drawBorder(leftFlag)  : FormScore::drawBorder(rightFlag));
    ui->rightFlag->setPixmap(isForJudge? FormScore::drawBorder(rightFlag) : FormScore::drawBorder(leftFlag) );

    setColor();

    ui->labelLeftHead->setText(QString("Round 1/%1 - Pending").arg(f->getCountOfRounds()));

    if (this->isForJudge)
    {
        pushButtonStart = new QRightClickButton();
        pushButtonStart->setText("Start (press SPACE)");
        pushButtonStart->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStart->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        pushButtonDoctor = new QRightClickButton();
        pushButtonDoctor->setText("Call a doctor");
        pushButtonDoctor->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonDoctor->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        cancelLastPenalty = new QRightClickButton();
        cancelLastPenalty->setText("Cancel last penalty (Minus, Fo, Ex)");
        cancelLastPenalty->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        cancelLastPenalty->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        pushButtonStop = new QRightClickButton();
        pushButtonStop->setText("Stop round");
        pushButtonStop->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStop->setFocusPolicy(Qt::FocusPolicy::NoFocus);


        QWidget * w = new QWidget();
        QGridLayout * l = new QGridLayout();
        w->setLayout(l);
        l->addWidget(pushButtonStart,   0, 0);
        l->addWidget(pushButtonDoctor,  0, 1);
        l->addWidget(cancelLastPenalty, 0, 2);
        l->addWidget(pushButtonStop,    0, 3);
        ui->gridLayoutMain->addWidget(w, 4, 0, 1, ui->gridLayoutMain->columnCount());
        ui->gridLayoutMain->setRowStretch(4, 8);


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



        connect(ui->leftLcdNumber , &MyQLCDNumber::leftButtonClick           , [f](){ f->addOnePointToLeftFighter(); });
        connect(ui->leftLcdNumber , &MyQLCDNumber::rightButtonClick          , [f](){ f->cancelLeftPoint(); });

        connect(ui->leftMinus     , &AspectRatioPixmapLabel::leftButtonClick , [f](){ f->addMinusToLeft(); });
        connect(ui->labelLeftMinus, &AspectRatioTextLabel::leftButtonClick   , [f](){ f->addMinusToLeft(); });

        connect(ui->leftFo        , &AspectRatioPixmapLabel::leftButtonClick , [f](){ f->addForestallingToLeft(); });
        connect(ui->labelLeftFo   , &AspectRatioTextLabel::leftButtonClick   , [f](){ f->addForestallingToLeft(); });

        connect(ui->leftEx        , &AspectRatioPixmapLabel::leftButtonClick , [f](){ f->addExToLeft(); });
        connect(ui->labelLeftEx   , &AspectRatioTextLabel::leftButtonClick   , [f](){ f->addExToLeft(); });



        connect(ui->rightLcdNumber , &MyQLCDNumber::leftButtonClick          , [f](){ f->addOnePointToRightFighter(); });
        connect(ui->rightLcdNumber , &MyQLCDNumber::rightButtonClick         , [f](){ f->cancelRightPoint(); });

        connect(ui->rightMinus     , &AspectRatioPixmapLabel::leftButtonClick, [f](){ f->addMinusToRight(); });
        connect(ui->labelRightMinus, &AspectRatioTextLabel::leftButtonClick  , [f](){ f->addMinusToRight(); });

        connect(ui->rightFo        , &AspectRatioPixmapLabel::leftButtonClick, [f](){ f->addForestallingToRight(); });
        connect(ui->labelRightFo   , &AspectRatioTextLabel::leftButtonClick  , [f](){ f->addForestallingToRight(); });

        connect(ui->rightEx        , &AspectRatioPixmapLabel::leftButtonClick, [f](){ f->addExToRight(); });
        connect(ui->labelRightEx   , &AspectRatioTextLabel::leftButtonClick  , [f](){ f->addExToRight(); });
    }

    connect(f, &Fighting::statusOrPointsChanged, this, &FightingTable2::updateInfo);

}

FightingTable2::~FightingTable2()
{
    delete ui;
}

void FightingTable2::setTextColor(QWidget *label, QColor color)
{
    QPalette localPalette = label->palette();
    localPalette.setColor(QPalette::ColorRole::WindowText, color);
    label->setPalette(localPalette);
}

void FightingTable2::setColor()
{
    QColor blue(0,191,255);
    QColor red(250,128,114);
    //QColor red(255,50,50);

    //QColor gray(169,169,169);
    QColor gray(192,192,192);


    ( isForJudge? ui->leftFlag : ui->rightFlag)->setGray(f->getWinner() == Fighting::Player::Right);
    (!isForJudge? ui->leftFlag : ui->rightFlag)->setGray(f->getWinner() == Fighting::Player::Left );

    if (f->getWinner() == Fighting::Player::Left)
    {

        setTextColor(ui->leftRegion     , isForJudge? red  : gray);
        setTextColor(ui->leftLcdNumber  , isForJudge? red  : gray);
        setTextColor(ui->labelLeftMinus , isForJudge? red  : gray);
        setTextColor(ui->labelLeftFo    , isForJudge? red  : gray);
        setTextColor(ui->labelLeftEx    , isForJudge? red  : gray);
        ui->leftMinus->setGray(isForJudge? false : true);
        ui->leftFo   ->setGray(isForJudge? false : true);
        ui->leftEx   ->setGray(isForJudge? false : true);


        setTextColor(ui->rightRegion    , isForJudge? gray : red);
        setTextColor(ui->rightLcdNumber , isForJudge? gray : red);
        setTextColor(ui->labelRightMinus, isForJudge? gray : red);
        setTextColor(ui->labelRightFo   , isForJudge? gray : red);
        setTextColor(ui->labelRightEx   , isForJudge? gray : red);
        ui->rightMinus->setGray(isForJudge? true : false);
        ui->rightFo   ->setGray(isForJudge? true : false);
        ui->rightEx   ->setGray(isForJudge? true : false);
    }
    else if (f->getWinner() == Fighting::Player::Right)
    {
        setTextColor(ui->leftRegion     , isForJudge? gray  : blue);
        setTextColor(ui->leftLcdNumber  , isForJudge? gray  : blue);
        setTextColor(ui->labelLeftMinus , isForJudge? gray  : blue);
        setTextColor(ui->labelLeftFo    , isForJudge? gray  : blue);
        setTextColor(ui->labelLeftEx    , isForJudge? gray  : blue);
        ui->leftMinus->setGray(isForJudge? true : false);
        ui->leftFo   ->setGray(isForJudge? true : false);
        ui->leftEx   ->setGray(isForJudge? true : false);


        setTextColor(ui->rightRegion    , isForJudge? blue : gray);
        setTextColor(ui->rightLcdNumber , isForJudge? blue : gray);
        setTextColor(ui->labelRightMinus, isForJudge? blue : gray);
        setTextColor(ui->labelRightFo   , isForJudge? blue : gray);
        setTextColor(ui->labelRightEx   , isForJudge? blue : gray);
        ui->rightMinus->setGray(isForJudge? false : true);
        ui->rightFo   ->setGray(isForJudge? false : true);
        ui->rightEx   ->setGray(isForJudge? false : true);
    }
    else
    {
        setTextColor(ui->leftRegion     , isForJudge? red : blue);
        setTextColor(ui->leftLcdNumber  , isForJudge? red : blue);
        setTextColor(ui->labelLeftMinus , isForJudge? red : blue);
        setTextColor(ui->labelLeftFo    , isForJudge? red : blue);
        setTextColor(ui->labelLeftEx    , isForJudge? red : blue);
        ui->leftMinus->setGray(false);
        ui->leftFo   ->setGray(false);
        ui->leftEx   ->setGray(false);

        setTextColor(ui->rightRegion    , isForJudge? blue : red);
        setTextColor(ui->rightLcdNumber , isForJudge? blue : red);
        setTextColor(ui->labelRightMinus, isForJudge? blue : red);
        setTextColor(ui->labelRightFo   , isForJudge? blue : red);
        setTextColor(ui->labelRightEx   , isForJudge? blue : red);

        ui->rightMinus->setGray(false);
        ui->rightFo   ->setGray(false);
        ui->rightEx   ->setGray(false);
    }


}

void FightingTable2::updateInfo()
{
    Fighting::FightStatus fightStatus = f->getStatus();

    if (f->getWinner() == Fighting::Player::NoPlayer)
        ui->labelTime->setText(f->getStringTime());
    else
        ui->labelTime->setText("");

    if (isForJudge)
    {
        if (fightStatus == Fighting::PendingExtraRound)
            pushButtonStart->setText("Start extra round! (press SPACE)");
        else if (fightStatus == Fighting::NotStart)
            pushButtonStart->setText("Start! (press SPACE)");
        else if (fightStatus == Fighting::PauseFight || fightStatus == Fighting::PauseExtraRound)
            pushButtonStart->setText("Continue (press SPACE)");
        else
            pushButtonStart->setText("Pause (press SPACE)");



        if (fightStatus == Fighting::DoctorOnRing)
            pushButtonDoctor->setText("Stop a doctor");
        else
            pushButtonDoctor->setText("Call a doctor");
    }



    if (fightStatus == Fighting::NotStart)
    {
        ui->labelLeftHead->setText(QString("Round 1/%1 - Not start").arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::Fight)
    {
        ui->labelLeftHead->setText(QString("Round %1/%2 - FIGHT!").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::Break)
    {

        ui->labelLeftHead->setText(QString("Round %1/%2 - Break").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));

        if (showAdvertisement)
        {
            if (10 * 1000 < f->getTimeMS())
            {
                if (!isForJudge && !isHidden())
                    hide();
            }
            else
            {
                if (!isForJudge  && isHidden())
                    show();
            }
        }
    }
    else if (fightStatus == Fighting::PauseFight)
    {
        ui->labelLeftHead->setText(QString("Round %1/%2 - Fight! - PAUSE").arg(f->getCurrentRound()).arg(f->getCountOfRounds()));
    }
    else if (fightStatus == Fighting::DoctorOnRing)
    {
        ui->labelLeftHead->setText("Doctor: " + f->getStringTimeDoctor());
    }
    else if (fightStatus == Fighting::Tie)
    {
        ui->labelLeftHead->setText("Tie...");
    }
    else if (fightStatus == Fighting::DisqualificationLeft)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::DisqualificationRight)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsLeft)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsRight)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsLeft10)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::winnerByPointsRight10)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::stoppedByJudge)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::forceLeftWinner)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::forceRightWinner)
    {
        ui->labelLeftHead->setText("");
    }
    else if (fightStatus == Fighting::PendingExtraRound)
    {
        ui->labelLeftHead->setText("Extra round - Not start");
    }
    else if (fightStatus == Fighting::ExtraRound)
    {
        ui->labelLeftHead->setText("Extra round - Fight!");
    }
    else if (fightStatus == Fighting::PauseExtraRound)
    {
        ui->labelLeftHead->setText("Extra round - Fight! - PAUSE");
    }






    ( isForJudge? ui->leftLcdNumber : ui->rightLcdNumber)->display(f->getCountOfPointsForLeftFighter());
    (!isForJudge? ui->leftLcdNumber : ui->rightLcdNumber)->display(f->getCountOfPointsForRightFighter());

    ( isForJudge? ui->leftMinus : ui->rightMinus)->setPixmap(FormScore::drawCubes(f->getCountOfMinusToLeft()));
    (!isForJudge? ui->leftMinus : ui->rightMinus)->setPixmap(FormScore::drawCubes(f->getCountOfMinusToRight()));

    ( isForJudge? ui->leftFo : ui->rightFo)->setPixmap(FormScore::drawCubes(f->getCountOfForestallingToLeft()));
    (!isForJudge? ui->leftFo : ui->rightFo)->setPixmap(FormScore::drawCubes(f->getCountOfForestallingToRight()));

    ( isForJudge? ui->leftEx : ui->rightEx)->setPixmap(FormScore::drawCubes(f->getCountOfExToLeft()));
    (!isForJudge? ui->leftEx : ui->rightEx)->setPixmap(FormScore::drawCubes(f->getCountOfExToRight()));

    setColor();
}

void FightingTable2::closeEvent(QCloseEvent* event)
{
    if (isForJudge)
    {
        if (f->getStatus() == Fighting::FightStatus::NotStart || f->getWinner() != Fighting::Player::NoPlayer)
        {
            event->accept(); // close window
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

void FightingTable2::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Escape);
    else if(e->key() == Qt::Key_Space)
    {
        if (isForJudge)
            f->pressedKeySpace();
    }
    //else QDialog::keyPressEvent(e);
}
