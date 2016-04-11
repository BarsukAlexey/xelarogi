#include "fighting_table.h"
#include "ui_fighting_table.h"

#include <QtGui>

using namespace std::chrono;

FightingTable::FightingTable(QWidget *parent, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, int durationOfRound, int durationOfBreak, int countOfRounds, QImage leftFlag, QImage rightFlag) :
    QDialog(parent),
    ui(new Ui::FightingTable),

    durationOfRound(durationOfRound),
    durationOfBreak(durationOfBreak),
    countOfRounds(countOfRounds)

//    durationOfRound(1),
//    durationOfBreak(2),
//    countOfRounds(1)
{
    ui->setupUi(this);

    ui->labelFIO_left->setText(nameLeft);
    ui->labelFIO_right->setText(nameRight);
    ui->labelRegion_left->setText(regionLeft);
    ui->labelRegion_right->setText(regionRight);


    mLeftFlag  = leftFlag .scaledToHeight(250);
    mRightFlag = rightFlag.scaledToHeight(250);
    ui->labelLeftFlag ->setPixmap(drawBorder(mLeftFlag ));
    ui->labelRightFlag->setPixmap(drawBorder(mRightFlag));

    status = Status::NotStart;
    ui->labelTime->setText(getTimeMMSS(this->durationOfRound));

    QTimer* timer = new QTimer(this);
    timer->start(poolTime);
    connect(timer, &QTimer::timeout, this, &FightingTable::update);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    resize(800, 600);

//    countPointLeft =  1 + rand()%1000;
//    countPointRight = 1 + rand()%1000;
//    status = Status::Finish;
//    gong->play();
//    molot->play();
}

FightingTable::~FightingTable()
{
    delete ui;
}

QString FightingTable::getTimeMMSS(long long time)
{
    return QString("%1").arg(time/60, 2, 10, QChar('0')) + ":" + QString("%1").arg(time%60, 2, 10, QChar('0'));
}

QPixmap FightingTable::drawBorder(QImage flag)
{
    QPixmap pm = QPixmap::fromImage(flag);
    QPainter painter(&pm);
    QPen pen(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRoundedRect(0, 0, flag.width() - 1, flag.height() - 1, 0, 0);
    return pm;
}

QImage FightingTable::makeGrey(QImage image)
{
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        int depth =4;
        for (int jj = 0; jj < image.width(); jj++) {
            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
            int gray = qGray(*rgbpixel);
            *rgbpixel = QColor(gray, gray, gray).rgba();
        }
    }
    return image;
}



void FightingTable::update()
{
    long long curTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long time = (curTime - startTime - sumOfDelay) / 1000;
    if (status == Status::NotStart)
    {
        ui->labelLeftHead->setText(QString("Round 1/%1 - Not start").arg(countOfRounds));
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
                sumOfDelay = 0;
                status = Status::Break;
            }
            update();
        }
        else
        {
            ui->labelLeftHead->setText(QString("Round %1/%2 - FIGHT!").arg(currentRound).arg(countOfRounds));
            ui->labelTime->setText(getTimeMMSS(durationOfRound - time));
        }
    }
    else if (status == Status::Break)
    {
        if (durationOfBreak - time <= 10 && molot->isFinished()){
            molot->play();
        }
        if (durationOfBreak <= time)
        {
            startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            sumOfDelay = 0;
            ++currentRound;
            status = Status::Fighting;
            molot->stop();
            gong->play();
            update();
        }
        else
        {
            ui->labelLeftHead->setText(QString("Round %1/%2 - Break").arg(currentRound).arg(countOfRounds));
            ui->labelTime->setText(getTimeMMSS(durationOfBreak - time));
        }
    }
    else if (status == Status::Pause)
    {
        ui->labelLeftHead->setText(QString("Round %1/%2 - Fight! - PAUSE").arg(currentRound).arg(countOfRounds));
    }
    else if (status == Status::DoctorOnRing)
    {
        long long x = durationOfDoctorOnRing - (curTime - startTimeDoctorOrPause) / 1000;
        if (0 < x)
            ui->labelDoctorTimer->setText(getTimeMMSS(x));
        else
            on_pushButtonDoctor_clicked();
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
        ui->labelLeftHead->setText("");

        QPalette palette = ui->labelTime->palette();
        palette.setColor(ui->labelTime->backgroundRole(), QColor(255, 255, 0));
        palette.setColor(ui->labelTime->foregroundRole(), QColor(255, 255, 0));
        ui->labelTime->setPalette(palette);
        ui->labelTime->setText(QString("Winner is ") + (countPointLeft > countPointRight? ui->labelFIO_left->text() : ui->labelFIO_right->text()));

        if (countPointLeft > countPointRight)
        {
            ui->widgetRight->setStyleSheet(QStringLiteral("background-color: rgb(169,169,169);"));
            ui->labelRightFlag->setPixmap(drawBorder(makeGrey(mRightFlag)));
        }
        else
        {
            ui->widgetLeft->setStyleSheet(QStringLiteral("background-color: rgb(169,169,169);"));
            ui->labelLeftFlag ->setPixmap(drawBorder(makeGrey(mLeftFlag )));
        }
    }
    ui->labelRightHead->setText(ui->labelLeftHead->text());
}


void FightingTable::on_pushButtonStart_clicked()
{
    if (status == Status::NotStart)
    {
        startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        sumOfDelay = 0;
        currentRound = 1;
        status = Status::Fighting;
        countPointLeft = 0;
        countPointRight = 0;
        ui->pushButtonStart->setText("Pause");
        gong->play();
    }
    else if (status == Status::Fighting)
    {
        status = Status::Pause;
        startTimeDoctorOrPause = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        update();
    }
    else if (status == Status::Pause)
    {
        sumOfDelay += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - startTimeDoctorOrPause;
        status = Status::Fighting;
        update();
    }
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


void FightingTable::on_pushButtonDoctor_clicked()
{
    if (status == Status::DoctorOnRing)
    {
        sumOfDelay += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - startTimeDoctorOrPause;
        status = Status::Fighting;
        ui->labelDoctorTimer->setText("");
        ui->pushButtonDoctor->setText("Call a doctor!");
        update();
    }
    else if (status == Status::Fighting)
    {
        status = Status::DoctorOnRing;
        startTimeDoctorOrPause = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        ui->pushButtonDoctor->setText("Stop doctor");
        update();
    }
}

QString FightingTable::getResult()
{
    return QString::number(countPointLeft) + " : " + QString::number(countPointRight);
}
