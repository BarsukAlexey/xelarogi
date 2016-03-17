#ifndef DBUTILS_H
#define DBUTILS_H

#include <QSqlDatabase>
#include <QStringList>
#include <QMap>
#include <algorithm>

class DBUtils
{

public:

    struct NodeOfTournirGrid
    {
        int v; // id вершины; вершины нумируются как в дереве отрезков (только зеркально)
        QString name;
        QString region;
        bool isFighing;
        long long UID;
        QString result;

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

    static QString getField(const QSqlDatabase&, const QString& field, const QString& table, const QString& UID);
    static QString getField(const QSqlDatabase&, const QString& field, const QString& table, const long long UID);
    static QString getFieldDate(const QSqlDatabase&, const QString& field, const QString& table, const long long UID);


    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);
    static QStringList get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& , long long);

    // для таблицы ORDERS
    static QString getSecondNameAndOneLetterOfName(const QSqlDatabase& database, long long UID);
    static QString get__REGION(const QSqlDatabase& database, long long UID);

    // для таблицы TOURNAMENTS
    static QString get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
    static QString get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID);
    static QString get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);


    // для таблицы GRID
    static QVector<NodeOfTournirGrid> getNodes(const QSqlDatabase& database, long long tournamentCategories);
    static QVector<NodeOfTournirGrid> getLeafOFTree(const QSqlDatabase& database, long long tournamentCategories);
    static QVector<QVector<DBUtils::Fighing>> getListsOfPairs(const QSqlDatabase& database, long long tournamentUID);
    static QVector<Fighing> getListOfPairs(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK);
    static bool setNodeOfGrid(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result);

    static int isPow2(int a) {
      return !(a & (a - 1));
    }

    // для таблицы TOURNAMENT_CATEGORIES
    static QVector<long long> get_UIDs_of_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long tournamentUID);
    static QString get__NAME_OF_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long UID);
    static QVector<std::tuple<long long, int, int, long long> > get_distinct_TYPE_FK_AgeFrom_AgeTill(const QSqlDatabase& database, long long tournamentUID);
    static QMap<QString, QVector<long long> > get_weight_and_orderUIDs(const QSqlDatabase& database, long long tournamentUID, long long type_fk, int age_from, int age_till, int sex_fk);
    static int     get__AGE_FROM(const QSqlDatabase& database, long long UID);
    static int     get__AGE_TILL(const QSqlDatabase& database, long long UID);
    static QString get__WEIGHT_FROM(const QSqlDatabase& database, long long UID);
    static QString get__WEIGHT_TILL(const QSqlDatabase& database, long long UID);
    static int     get__DURATION_FIGHING(const QSqlDatabase& database, long long UID);
    static int     get__DURATION_BREAK(const QSqlDatabase& database, long long UID);
    static int     get__ROUND_COUNT(const QSqlDatabase& database, long long UID);
    static QString getNormanWeightRange(const QSqlDatabase& database, long long uidCategory);


    static QString roundDouble(double x, int precision);

};

#endif // DBUTILS_H
