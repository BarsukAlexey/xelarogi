#ifndef FIGHTING_H
#define FIGHTING_H

#include <chrono>

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QImage>
#include <QStack>
#include <QSound>
#include <QTimer>

using namespace std::chrono;

class Fighting : public QObject
{
    Q_OBJECT

public:
    enum FightStatus
    {
        NotStart, Fight, Break, PauseFight, DoctorOnRing, Tie, DisqualificationLeft, DisqualificationRight,
        winnerByPointsLeft, winnerByPointsRight,
        winnerByPointsLeft10, winnerByPointsRight10,
        stoppedByJudge, forceLeftWinner, forceRightWinner,
        PendingExtraRound, ExtraRound, PauseExtraRound
    };
    QStringList statusName;

    enum Player
    {
        Left, Right, NoPlayer
    };

    enum Penalty
    {
        Minus, Ex, FO
    };
private:
    class Item
    {
    public:
        Penalty penalty;
        Player player;
        int deltaLeft;
        int deltaRight;

        Item() :
            penalty(Penalty::Minus),
            player(Player::Left)
        {
        }

        Item(Penalty penalty, Player player) :
            penalty(penalty),
            player(player)
        {
            deltaLeft = 0;
            deltaRight = 0;
        }
    };

    long long prevMomentTime;
    long long spendTime;

    long long spentTimeDoctor;
    const int durationOfDoctorOnRing;

    int currentRound;
    const int durationOfRound;
    const int durationOfBreak;
    const int countOfRounds;
    const int durationOfExtraRound;

    FightStatus status;
    FightStatus statusBeforDisqualification;
    FightStatus fightStatusBeforDialog;

    int countPointLeft;
    int countPointRight;
    int countOfMinusToLeft;
    int countOfMinusToRight;
    int countOfForestallingToLeft;
    int countOfForestallingToRight;
    int countOfExToLeft;
    int countOfExToRight;
    bool wasExtraRound;

    QString forceResult = "sd";

    QStack<Item> stackPenalty;

    QSound *soundGong = new QSound("resources\\sounds\\gong.wav");
    QSound *soundHummerBit = new QSound("resources\\sounds\\stuk_molotka.wav");

    QTimer *timer;

public:
    explicit Fighting(int durationOfRound, int durationOfBreak, int countOfRounds, int durationOfExtraRound);

private:
    void updateTime();
    void updatePointStatus();

public:
    void dispose();
    void setDialog(bool dialog);
    void forceStopRound(Player player, QString forceResult);

    bool isDisqOrPoint10OrForceWinner();
    void disqualify(Player player);

    void addOnePointToLeftFighter();
    void addOnePointToRightFighter();
    void cancelLeftPoint();
    void cancelRightPoint();

    void addMinusToLeft();
    void addMinusToRight();

    void addForestallingToLeft();
    void addForestallingToRight();

    void addExToLeft();
    void addExToRight();


    void pressedKeySpace();
    void pressDoctor();

    int getCountOfPointsForLeftFighter() const;
    int getCountOfPointsForRightFighter() const;

    static QString getTimeMMSS(long long timeMS);
    QString getStringTime() const;
    long long getTimeMS() const;
    QString getStringTimeDoctor() const;

    QString getResult();
    Player getWinner();

    void cancelLastAction();

    FightStatus getStatus() const;
    int getDurationOfRound() const;
    int getCountOfRounds() const;
    int getCurrentRound() const;

    int getCountOfMinusToLeft() const;
    int getCountOfMinusToRight() const;
    int getCountOfForestallingToLeft() const;
    int getCountOfForestallingToRight() const;
    int getCountOfExToLeft() const;
    int getCountOfExToRight() const;









signals:

public slots:
};

#endif // FIGHTING_H
