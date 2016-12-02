#pragma once
#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QIODevice>

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
    void loadMusic(const QString& path, bool startPlay = false);
    void setRawData(const QByteArray& rawData, bool startPlay = false);
    ~SoundPlayer();
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void setTitle(const QString& text);
    const QString randomString;

private:
    QString msecsToString(qint64 n);

private:
    QMediaPlayer* mediaPlayer;
    Ui::SoundPlayer* ui;
    QByteArray blob;
//    QBuffer buffer;



private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

public slots:
    void onSomePlayerStarPlayMusic();

signals:
    iPlayMusic();
    giveMeNextMusic();
};
