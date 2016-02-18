#ifndef BDUTILS_H
#define BDUTILS_H

#include <QSqlDatabase>
#include <QStringList>

class BDUtils
{

public:

    struct NodeOfTournirGrid
    {
        int v; // id вершины; вершины нумируются как в дереве отрезков (только зеркально)
        QString name;
        QString region;
        bool isFighing;
        long long UID;

        bool operator < (const NodeOfTournirGrid& other) const
        {
            return v < other.v;
        }
    };

    struct Fighing
    {
        long long UID0;
        long long UID1;
        long long VERTEX;
        long long TOURNAMENT_CATEGORIES_FK;
        int winer;
    };

    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);
    static QStringList get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& , long long);

    static QString get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
    static QString get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID);
    static QString get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);

    static QVector<NodeOfTournirGrid> getNodes(const QSqlDatabase& database, long long tournamentCategories);
    static QVector<QVector<BDUtils::Fighing>> getListsOfPairs(const QSqlDatabase& database, long long tournamentUID);
    static QVector<Fighing> getListOfPairs(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK);

    static int isPow2(int a) {
      return !(a & (a - 1));
    }

    static QString get_NAME_FROM_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long UID);

    static double get__AGE_TILL__FROM__TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long UID);
};

#endif // BDUTILS_H
