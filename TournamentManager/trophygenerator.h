#ifndef TROPHYGENERATOR_H
#define TROPHYGENERATOR_H

#include <QAxWidget>
#include <QAxObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>
#include <QFileDialog>

#include "db_utils.h"
#include "excel_utils.h"
#include "trophygeneratorsettingsdialog.h"

class TrophyGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TrophyGenerator(const long long tournamentUID, QObject *parent = 0);

signals:

public slots:

private:
    long long mTournamentUID;
};

#endif // TROPHYGENERATOR_H
