#ifndef FIGHTING_TABLE_H
#define FIGHTING_TABLE_H

#include <QWidget>

namespace Ui {
class FightingTable;
}

class FightingTable : public QWidget
{
    Q_OBJECT


    enum Status
    {
        NotStart, Fighting, Break, DoctorOnRing, Tie, Finish
    };

private:
    const int poolTime = 200;
    long long startTime;
    long long sumOfDelay;
    int currentRound;
    const int countOfRounds = 2;
    const int durationOfRound = 5;
    const int durationOfBreak = 3;
    Status status;
    int countPointLeft;
    int countPointRight;

public:
    explicit FightingTable(QWidget *parent = 0);
    ~FightingTable();

private:
    Ui::FightingTable *ui;

private slots:
    void update();
    void on_pushButtonStart_clicked();
    void on_pushButtonPointLeft_clicked();
    void on_pushButtonPointRight_clicked();
};

#endif // FIGHTING_TABLE_H
