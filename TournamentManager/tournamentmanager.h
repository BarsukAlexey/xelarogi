#ifndef TOURNAMENTMANAGER_H
#define TOURNAMENTMANAGER_H

#include <iostream>
#include <algorithm>

#include <QObject>
#include <QString>
#include <QVector>

class TournamentManager : public QObject
{
    Q_OBJECT
public:
    struct InitialParticapantRecord {
       QString text;
       int priorityOrder;
       int regionFK;
       bool operator < (const InitialParticapantRecord& other) const
       {
           if (priorityOrder != other.priorityOrder)
               return regionFK < other.regionFK;
           return priorityOrder > other.priorityOrder;
       }
    };
    struct Point {
        int x, y;
    };
    struct Border {
        Point p;
        bool l, t, r, b;
    };

    static QVector<TournamentManager::InitialParticapantRecord> getTournamentInitialState(QVector<TournamentManager::InitialParticapantRecord> particapants);
    static QVector<QVector<TournamentManager::Point>> getTournamentRectangles(QVector<TournamentManager::InitialParticapantRecord> particapants);
    static QVector<TournamentManager::Border> getTournamentBorders(QVector<QVector<TournamentManager::Point>> levels);
    static QVector<TournamentManager::InitialParticapantRecord> getSavedRecords();

private:
    TournamentManager() = default;
    TournamentManager(const TournamentManager&) = delete;
    TournamentManager operator= (const TournamentManager&) = delete;

private:
    static TournamentManager& instance();

private:
    QVector<TournamentManager::InitialParticapantRecord> mRecords;
};

#endif // TOURNAMENTMANAGER_H
