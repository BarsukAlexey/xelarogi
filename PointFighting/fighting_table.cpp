
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

    if (!dialogForJudge)
    {
        left  = new FormScore(nameRight, regionRight, rightFlag, Qt::blue);
        right = new FormScore(nameLeft , regionLeft , leftFlag , Qt::red );
        ui->horizontalLayoutMain->addWidget(left );
        ui->horizontalLayoutMain->addWidget(right);
    }
    else
    {
        left  = new FormScore(nameLeft , regionLeft , leftFlag , Qt::red );
        right = new FormScore(nameRight, regionRight, rightFlag, Qt::blue);
        ui->horizontalLayoutMain->addWidget(left , 50);
        ui->horizontalLayoutMain->addWidget(right, 50);


        pushButtonStart = new QRightClickButton();
        pushButtonStart->setText("Start (press SPACE)");
        pushButtonStart->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStart->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        ui->widgetFooterHorizontalLayout->insertWidget(0, pushButtonStart);

        pushButtonDoctor = new QRightClickButton();
        pushButtonDoctor->setText("Call a doctor");
        pushButtonDoctor->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonDoctor->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        ui->widgetFooterHorizontalLayout->insertWidget(1, pushButtonDoctor);

        cancelLastPenalty = new QRightClickButton();
        cancelLastPenalty->setText("Cancel last penalty (Minus, Fo, Ex)");
        cancelLastPenalty->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        cancelLastPenalty->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        ui->widgetFooterHorizontalLayout->insertWidget(2, cancelLastPenalty);

        pushButtonStop = new QRightClickButton();
        pushButtonStop->setText("Stop round");
        pushButtonStop->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStop->setFocusPolicy(Qt::FocusPolicy::NoFocus);
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

        connect(left ->ui->pushButtonPoint, &QRightClickButton::clicked, [f](){f->addOnePointToLeftFighter();} );
        connect(right->ui->pushButtonPoint, &QRightClickButton::clicked, [f](){f->addOnePointToRightFighter();});
        connect(left ->ui->pushButtonPoint, &QRightClickButton::rightClicked, [f](){f->cancelLeftPoint();});
        connect(right->ui->pushButtonPoint, &QRightClickButton::rightClicked, [f](){f->cancelRightPoint();});

        connect(left ->ui->pushButtonMinus, &QRightClickButton::clicked, [f](){f->addMinusToLeft();});
        connect(right->ui->pushButtonMinus, &QRightClickButton::clicked, [f](){f->addMinusToRight();});

        connect(left ->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToLeft(); });
        connect(right->ui->pushButtonFo, &QRightClickButton::clicked, [f](){ f->addForestallingToRight(); });

        connect(left ->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToLeft();});
        connect(right->ui->pushButtonEx, &QRightClickButton::clicked, [f](){f->addExToRight();});
    }


    connect(f, SIGNAL(statusOrPointsChanged()), this, SLOT(updateInfo()));
    //showMaximized();
    updateInfo();
}

FightingTable::~FightingTable()
{
    delete ui;
}



void FightingTable::updateInfo()
{

    Fighting::FightStatus fightStatus = f->getStatus();



    if (fightStatus == Fighting::DoctorOnRing)
        ui->labelDoctorTimer->setText("Doctor: " + f->getStringTimeDoctor());
    else
        ui->labelDoctorTimer->setText("");



    if (f->getWinner() == Fighting::Player::NoPlayer)
        ui->labelTime->setText(f->getStringTime());
    else
        ui->labelTime->setText(f->getResult());



    if (dialogForJudge)
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
                if (!dialogForJudge && !isHidden())
                    hide();
            }
            else
            {
                if (!dialogForJudge  && isHidden())
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



    ui->labelRightHead->setText(ui->labelLeftHead->text());

    FormScore *l, *r;
    if (dialogForJudge)
        l = left, r = right;
    else
        r = left, l = right;

    l->setCountPoints(f->getCountOfPointsForLeftFighter());
    l->setCountMinus(f->getCountOfMinusToLeft());
    l->setCountFo(f->getCountOfForestallingToLeft());
    l->setCountEx(f->getCountOfExToLeft());
    l->setWinner(f->getWinner() != Fighting::Player::Right);  // true if non or left

    r->setCountPoints(f->getCountOfPointsForRightFighter());
    r->setCountMinus(f->getCountOfMinusToRight());
    r->setCountFo(f->getCountOfForestallingToRight());
    r->setCountEx(f->getCountOfExToRight());
    r->setWinner(f->getWinner() != Fighting::Player::Left); // true if non or right
}

void FightingTable::closeEvent(QCloseEvent* event)
{
    if (dialogForJudge)
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

void FightingTable::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Escape);
    else if(e->key() == Qt::Key_Space)
    {
        if (dialogForJudge)
            f->pressedKeySpace();
    }
    else
        QDialog::keyPressEvent(e);
}
