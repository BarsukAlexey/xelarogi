#include "fightingtable2.h"
#include "ui_fightingtable2.h"

FightingTable2::FightingTable2(Fighting* f, QString categoty, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, QImage leftFlag, QImage rightFlag, bool isForJudge, bool showAdvertisement, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FightingTable2),
    f(f),
    isForJudge(isForJudge),
    showAdvertisement(showAdvertisement)
{
    ui->setupUi(this);

    ui->labelCategory->setText(categoty);

    ui->leftName ->setText(isForJudge? nameLeft  : nameRight);
    ui->rightName->setText(isForJudge? nameRight : nameLeft );

    ui->leftRegion ->setText(isForJudge? regionLeft  : regionRight);
    ui->rightRegion->setText(isForJudge? regionRight : regionLeft );

    ui->leftFlag ->setPixmap(isForJudge? FormScore::drawBorder(leftFlag)  : FormScore::drawBorder(rightFlag));
    ui->rightFlag->setPixmap(isForJudge? FormScore::drawBorder(rightFlag) : FormScore::drawBorder(leftFlag) );

    setTextColor(ui->leftRegion, isForJudge? Qt::red : Qt::blue);
    setTextColor(ui->leftLcdNumber, isForJudge? Qt::red : Qt::blue);
    setTextColor(ui->labelLeftMinus, isForJudge? Qt::red : Qt::blue);
    setTextColor(ui->labelLeftFo, isForJudge? Qt::red : Qt::blue);
    setTextColor(ui->labelLeftEx, isForJudge? Qt::red : Qt::blue);

    setTextColor(ui->rightRegion, isForJudge? Qt::blue : Qt::red);
    setTextColor(ui->rightLcdNumber, isForJudge? Qt::blue : Qt::red);
    setTextColor(ui->labelRightMinus, isForJudge? Qt::blue : Qt::red);
    setTextColor(ui->labelRightFo, isForJudge? Qt::blue : Qt::red);
    setTextColor(ui->labelRightEx, isForJudge? Qt::blue : Qt::red);


    ui->labelStatus->setText(QString("Round 1/%1 - Pending").arg(f->getCountOfRounds()));

    if (isForJudge)
    {
        pushButtonStart = new QRightClickButton();
        pushButtonStart->setText("Start (press SPACE)");
        pushButtonStart->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStart->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        //ui->widgetFooterHorizontalLayout->insertWidget(0, pushButtonStart);

        pushButtonDoctor = new QRightClickButton();
        pushButtonDoctor->setText("Call a doctor");
        pushButtonDoctor->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonDoctor->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        //ui->widgetFooterHorizontalLayout->insertWidget(1, pushButtonDoctor);

        cancelLastPenalty = new QRightClickButton();
        cancelLastPenalty->setText("Cancel last penalty (Minus, Fo, Ex)");
        cancelLastPenalty->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        cancelLastPenalty->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        //ui->widgetFooterHorizontalLayout->insertWidget(2, cancelLastPenalty);

        pushButtonStop = new QRightClickButton();
        pushButtonStop->setText("Stop round");
        pushButtonStop->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
        pushButtonStop->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        //ui->widgetFooterHorizontalLayout->insertWidget(3, pushButtonStop);


        ui->gridLayoutMain->addWidget(pushButtonStart);


        connect(ui->leftMinus, &AspectRatioTextLabel::leftButtonClick, [this](){ qDebug() << "Click tutu"; });
    }
}

FightingTable2::~FightingTable2()
{
    delete ui;
}

void FightingTable2::setTextColor(QWidget *label, Qt::GlobalColor color)
{
    QPalette localPalette = label->palette();
    localPalette.setColor(QPalette::ColorRole::WindowText, color);
    label->setPalette(localPalette);
}
