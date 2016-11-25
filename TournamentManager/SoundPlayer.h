#include <QWidget>
#include <QMediaPlayer>

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

private:
    QString msecsToString(qint64 n);

private:
    QMediaPlayer* mediaPlayer;
    Ui::SoundPlayer* ui;



private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64             );
    void slotStatusChanged(QMediaPlayer::State);
};
