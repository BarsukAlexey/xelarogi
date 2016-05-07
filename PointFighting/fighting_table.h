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
#include "ui_fighting_table.h"
#include "ui_form.h"
#include "formscore.h"
#include <QtGui>

namespace Ui {
class FightingTable;
}

class FightingTable : public QDialog
{
    Q_OBJECT

public:
    enum Status
    {
        NotStart, Fighting, Break, Pause, DoctorOnRing, Tie, Finish, DisqualificationLeft, DisqualificationRight,
        winnerByPointsLeft, winnerByPointsRight,
        stopedByJudge, forceLeftWinner, forceRightWinner,
        PendingExtraRound, ExtraRound, PauseExtraRound
    };

    enum Player
    {
        LeftPlayer, RightPlayer, NoPlayer
    };



private:
    Ui::FightingTable *ui;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonDoctor;
    QPushButton *pushButtonStop;

    const QString nameLeft, nameRight;
    const int poolTime = 200;
    long long prevTime;
    long long spentTime;

    long long spentTimeDoctor;
    const int durationOfDoctorOnRing;

    int currentRound;
    const int durationOfRound;
    const int durationOfBreak;
    const int countOfRounds;
    const int durationExtraRound;
    const QImage mLeftFlag;
    const QImage mRightFlag;
public:
    Status status;
private:
    Status statusBeforDisqualification;
    int countPointLeft;
    int countPointRight;
    int countOfLeftMinus;
    int countOfRightMinus;
    QStack<std::pair<int, int> > stackMinusLeft;
    QStack<std::pair<int, int> > stackMinusRight;
    int countOfLeftFo;
    int countOfRightFo;
    int countOfLeftEx;
    int countOfRightEx;
    QStack<std::pair<int, int> > stackLeftEx;
    QStack<std::pair<int, int> > stackRightEx;

    QSound *gong = new QSound("resources\\sounds\\gong.wav");
    QSound *molot = new QSound("resources\\sounds\\stuk_molotka.wav");

    QVector<FormScore*> left, right;
    QVector<FightingTable*> allTables;
    const bool dialogForJudge;
    const bool showAdvertisement;

    QString forceResult;

public:
    explicit FightingTable(QWidget *parent, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, int durationOfRound, int durationOfBreak, int countOfRounds, QImage leftFlag, QImage rightFlag, bool dialogForJudge, bool showAdvertisement, int durationExtraRound);
    ~FightingTable();

private:
    static QString getTimeMMSS(long long time);


private slots:
    void update();
    void on_pushButtonStart_clicked();
    void on_pushButtonDoctor_clicked();

    void on_pushButtonPointLeft_clicked();
    void on_pushButtonPointRight_clicked();
    void on_pushButtonAbortPointLeft_clicked();
    void on_pushButtonAbortPointRight_clicked();

    void on_pushButtonAddMinusLeft_clicked();
    void on_pushButtonAddMinusRight_clicked();
    void on_pushButtonAbortMinusLeft_clicked();
    void on_pushButtonAbortMinusRight_clicked();

    void on_pushButtonAddExLeft_clicked();
    void on_pushButtonAddExRight_clicked();
    void on_pushButtonAbortExLeft_clicked();
    void on_pushButtonAbortExRight_clicked();

public:
    QString getResult();
    Player getWinner();


protected:
    void closeEvent(QCloseEvent *event)
    {
        if (dialogForJudge)
        {
            if (status == Status::NotStart || getWinner() != Player::NoPlayer)
            {
                event->accept(); // close window
                for (FightingTable* f : allTables)
                    f->hide();
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
};

#endif // FIGHTING_TABLE_H
