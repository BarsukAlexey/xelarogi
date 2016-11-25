#include <QtWidgets>
#include "SoundPlayer.h"
#include "ui_soundplayer.h"

// ----------------------------------------------------------------------
SoundPlayer::SoundPlayer(QWidget* pwgt) :
    QWidget(pwgt),
    ui(new Ui::SoundPlayer)
{
    ui->setupUi(this);

    ui->labelCurrent->setText(msecsToString(0));
    ui->labelRemain->setText(msecsToString(0));
    mediaPlayer = new QMediaPlayer;

    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    ui->sliderPosition->setRange(0, 0);
    ui->sliderPosition->setOrientation(Qt::Horizontal);

    ui->sliderVolume->setRange(0, 100);
    int defaultVolume = 50;
    mediaPlayer->setVolume(defaultVolume);
    ui->sliderVolume->setValue(defaultVolume);

    connect(ui->pushButtonOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(ui->pushButtonPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(ui->pushButtonStop, SIGNAL(clicked()), mediaPlayer, SLOT(stop()));
    connect(ui->sliderVolume, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));

    connect(ui->sliderPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));

    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));
}

void SoundPlayer::slotOpen()
{
    QString strFile = QFileDialog::getOpenFileName(this, "Open File");
    if (!strFile.isEmpty()) {
        ui->labelPath->setText(strFile);
        mediaPlayer->setMedia(QUrl::fromLocalFile(strFile));
        ui->pushButtonPlay->setEnabled(true);
        ui->pushButtonStop->setEnabled(true);
    }
}

void SoundPlayer::slotPlay()
{
    switch(mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void SoundPlayer::slotSetMediaPosition(int n)
{
    mediaPlayer->setPosition(n);
}

void SoundPlayer::slotSetDuration(qint64 n)
{
    ui->sliderPosition->setRange(0, n);
    ui->labelCurrent->setText(msecsToString(0));
    ui->labelRemain->setText(msecsToString(n));
}

void SoundPlayer::slotStatusChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void SoundPlayer::slotSetSliderPosition(qint64 n)
{
    ui->sliderPosition->setValue(n);

    int nDuration = ui->sliderPosition->maximum();
    ui->labelCurrent->setText(msecsToString(n));
    ui->labelRemain->setText(msecsToString(nDuration - n));
}

QString SoundPlayer::msecsToString(qint64 n)
{
    int nHours   = (n / (60 * 60 * 1000));
    int nMinutes = ((n  % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

