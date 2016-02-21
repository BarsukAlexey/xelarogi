#ifndef EBNUTVBAZU_H
#define EBNUTVBAZU_H

#include <QSqlDatabase>

class EbnutVBazu
{
public:

    static void f(const QSqlDatabase &_database, long long _tournamentUID);

    static void setRandomWinner(const QSqlDatabase &_database, long long _tournamentUID);

};

#endif // EBNUTVBAZU_H
