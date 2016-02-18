#ifndef BDUTILS_H
#define BDUTILS_H

#include <QSqlDatabase>

class BDUtils
{

public:
    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);
    static QStringList get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& , long long);

    static QString get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
    static QString get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID);
    static QString get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
};

#endif // BDUTILS_H
