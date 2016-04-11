#ifndef FIGHTING_TABLE_H
#define FIGHTING_TABLE_H

#include <QWidget>
#include <QDialog>
#include <QSound>
#include <QCloseEvent>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <chrono>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include <QMessageBox>


namespace Ui {
class FightingTable;
}

class FightingTable : public QDialog
{
    Q_OBJECT

public:
    enum Status
    {
        NotStart, Fighting, Break, Pause, DoctorOnRing, Tie, Finish
    };


private:
    Ui::FightingTable *ui;
    const int poolTime = 200;
    long long startTime;
    long long sumOfDelay;
    int currentRound;
    const int durationOfRound = 5;
    const int durationOfBreak = 3;
    const int countOfRounds = 2;
    QImage mLeftFlag;
    QImage mRightFlag;
public:
    Status status;
    int countPointLeft;
    int countPointRight;
private:
    long long startTimeDoctorOrPause;
    const int durationOfDoctorOnRing = 2 * 60;
    QSound *gong = new QSound("resources\\sounds\\gong.wav");
    QSound *molot = new QSound("resources\\sounds\\stuk_molotka.wav");

public:
    explicit FightingTable(QWidget *parent, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, int durationOfRound, int durationOfBreak, int countOfRounds, QImage leftFlag, QImage rightFlag);
    ~FightingTable();

private:
    static QString getTimeMMSS(long long time);
    static QPixmap drawBorder(QImage flag);
    static QImage makeGrey(QImage flag);

private slots:
    void update();
    void on_pushButtonStart_clicked();
    void on_pushButtonPointLeft_clicked();
    void on_pushButtonPointRight_clicked();
    void on_pushButtonDoctor_clicked();

public:
    QString getResult();

protected:
    void closeEvent(QCloseEvent *event) {
        if (status == Status::NotStart || status == Status::Finish)
        {
            event->accept(); // close window
            return;
        }
        event->ignore(); // keep window
        QMessageBox::warning(this, "", "Contest is not finished.\nDon't close this window!");

    }
};

#endif // FIGHTING_TABLE_H
