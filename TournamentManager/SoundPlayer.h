#pragma once
#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QIODevice>
#include <QMediaContent>
#include <QDataStream>


class QPushButton;
class QSlider;
class QLabel;
class QVBoxLayout;

namespace Ui {
class SoundPlayer;
}

class SoundPlayer : public QWidget {
    Q_OBJECT

public:
    SoundPlayer(QWidget* pwgt = 0);
    QByteArray getRawData();
    void setRawData(const QByteArray& rawData);
    ~SoundPlayer();
    const QString randomString;

private:
    QString msecsToString(qint64 n);

private:
    QMediaPlayer* mediaPlayer;
    Ui::SoundPlayer* ui;
    QByteArray blob;
    //QBuffer buffer;



private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64             );
    void slotStatusChanged(QMediaPlayer::State);
    void on_pushButtonDelete_clicked();

    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};
