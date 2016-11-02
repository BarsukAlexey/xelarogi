#ifndef EBNUTVBAZU_H
#define EBNUTVBAZU_H

#include "db_utils.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>
#include <utility>
#include <QSqlDatabase>

class EbnutVBazu
{
public:

    static void f(const QSqlDatabase &_database, long long _tournamentUID);

    static void setRandomWinner();

    static void setTournamentCat(long long tournamentUID);

};

#endif // EBNUTVBAZU_H
