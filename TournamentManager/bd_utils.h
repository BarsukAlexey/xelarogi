#ifndef BDUTILS_H
#define BDUTILS_H

#include <QSqlDatabase>

class BDUtils
{

public:
    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);

};

#endif // BDUTILS_H
