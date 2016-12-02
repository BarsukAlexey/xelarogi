#include <QtWidgets>
#include "SoundPlayer.h"
#include "ui_soundplayer.h"

// ----------------------------------------------------------------------
SoundPlayer::SoundPlayer(QWidget* pwgt) :
    QWidget(pwgt),
    randomString("trash\\" + QString::number(rand())),
    ui(new Ui::SoundPlayer)
{
    ui->setupUi(this);

    ui->labelCurrent->setText(msecsToString(0));
    ui->labelRemain->setText(msecsToString(0));
    mediaPlayer = new QMediaPlayer;


    ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    ui->sliderPosition->setRange(0, 0);
    ui->sliderPosition->setOrientation(Qt::Horizontal);

    ui->sliderVolume->setRange(0, 100);

    QSettings settings;
    int volume = settings.value("soundplayer/volume", 50).toInt();

    mediaPlayer->setVolume(volume);
    ui->sliderVolume->setValue(volume);

    //connect(ui->pushButtonOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(ui->pushButtonPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(ui->pushButtonStop, SIGNAL(clicked()), mediaPlayer, SLOT(stop()));
    connect(ui->sliderVolume, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));

    connect(ui->sliderPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));

    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));
    connect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));


    //    slotOpen();
}

QByteArray SoundPlayer::getRawData()
{
    return blob;
}

void SoundPlayer::loadMusic(const QString& path, bool startPlay)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    ui->labelPath->setText(QFileInfo(file.fileName()).fileName());

    blob = file.readAll();
    setRawData(blob, startPlay);
}

void SoundPlayer::setRawData(const QByteArray& rawData, bool startPlay)
{
//    blob = rawData;

//    buffer.close();
//    buffer.setBuffer(&blob);
//    if (!buffer.open(QIODevice::ReadOnly))
//        return;

//    mediaPlayer->setMedia(QMediaContent(), &buffer);
//    if (startPlay)
//    {
//        mediaPlayer->play();
//        emit iPlayMusic();
//    }

    blob = rawData;
    mediaPlayer->setMedia(QMediaContent());
    {
        QFile file(randomString);
        if (!file.open(QIODevice::WriteOnly))
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "!buffer.open";
        qDebug() << "I write bites: " << file.write(blob);
        file.flush();
        file.close();
    }
    mediaPlayer->setMedia(QUrl::fromLocalFile(randomString));
    if (startPlay)
    {
        mediaPlayer->play();
        emit iPlayMusic();
    }
}

SoundPlayer::~SoundPlayer()
{
    QSettings settings;
    settings.setValue("soundplayer/volume", mediaPlayer->volume());

    mediaPlayer->stop();
    delete mediaPlayer;
    delete ui;
}

QSize SoundPlayer::sizeHint() const
{
    //qDebug() << "sizeHint";
    return QSize(300, 100);
}

void SoundPlayer::setTitle(const QString& text)
{
    ui->labelPath->setText(text);
}

void SoundPlayer::slotOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    blob = file.readAll();
    qDebug() << "blob.size():" << blob.size() / 1024. / 1024.;

    setRawData(blob);
}

void SoundPlayer::slotPlay()
{

    switch(mediaPlayer->state())
    {
        case QMediaPlayer::PlayingState:
            mediaPlayer->pause();
        break;
        default:
            if (blob.size())
            {
                mediaPlayer->play();
                emit iPlayMusic();
            }
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
    switch(state)
    {
        case QMediaPlayer::PlayingState:
            ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        default:
            ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
    }
}

void SoundPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
        emit giveMeNextMusic();
}

void SoundPlayer::onSomePlayerStarPlayMusic()
{
    if (mediaPlayer->state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer->pause();
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


//void SoundPlayer::on_pushButtonDelete_clicked()
//{
//    mediaPlayer->setMedia(QMediaContent());
//    buffer.close();
//    blob.clear();
//}
