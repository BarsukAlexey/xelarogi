#ifndef DBUTILS_H
#define DBUTILS_H

#include <QSqlDatabase>
#include <QStringList>
#include <QMap>
#include <QDate>
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

        bool operator < (const Fighing& other) const
        {
            return VERTEX < other.VERTEX;
        }
    };

    static QString getField(const QString& field, const QString& table, const QString& UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getField(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getFieldDate(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QDate getFieldDateAsDate(const QSqlDatabase& database, const QString& field, const QString& table, const long long UID);
    static QString getRussianMonth(int m);

    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);
    static QStringList get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& , long long);

    // для таблицы ORDERS
    static QString getSecondNameAndOneLetterOfName(long long UID);
    static QString get__REGION(const QSqlDatabase& database, long long UID);
    static QSet<long long> getSetOfOrdersInTournamentCategory(long long uidTournamentCategory);
    static int getAge(QDate DATE_WEIGHTING, QDate birthdayDate);

    // для таблицы TOURNAMENTS
    static QString get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
    static QString get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID);
    static QString get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);


    // для таблицы GRID
    static QVector<NodeOfTournirGrid> getNodes(long long tournamentCategoryUID);
    static QVector<QVector<NodeOfTournirGrid>> getNodesAsLevelListOfList(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getLeafOFTree(const QSqlDatabase& database, long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getFightingNodes(long long tournamentCategoryUID);
    static QVector<QVector<DBUtils::Fighing>> getListsOfPairsForFighting(long long tournamentUID);
    static QVector<Fighing> getListOfPairsForFighting(long long TOURNAMENT_CATEGORIES_FK);
    static QVector<Fighing> getListOfPairsForFightingForPointFighting(long long TOURNAMENT_CATEGORIES_FK);
    static void insertLeafOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID);
    static bool updateNodeOfGrid(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result);
    static void swapNodesOfGrid(long long tournamentCategoryUID, int node0v, int node1v);
    static int findDurationOfGrid(long long tournamentCategoryUID, int delay = 0);
    static int findDurationOfFightinPair(long long tournamentCategoryUID);

    static  QVector<long long> getUidOfWinner(long long UIDtournamentCategory, int countOfWinners);
    static int isPow2(int a) {
      return !(a & (a - 1));
    }

    // для таблицы TOURNAMENT_CATEGORIES
    static QVector<long long> get_UIDs_of_TOURNAMENT_CATEGORIES(long long tournamentUID);
    //static QString get__NAME_OF_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long UID);
    static QVector<std::tuple<long long, int, int, long long> > get_distinct_TYPE_FK_AgeFrom_AgeTill(long long tournamentUID);
    static QMap<QString, QVector<long long> > get_weight_and_orderUIDs(long long tournamentUID, long long type_fk, int age_from, int age_till, int sex_fk);
    static int     get__AGE_FROM(const QSqlDatabase& database, long long UID);
    static int     get__AGE_TILL(const QSqlDatabase& database, long long UID);
    static QString get__WEIGHT_FROM(const QSqlDatabase& database, long long UID);
    static QString get__WEIGHT_TILL(const QSqlDatabase& database, long long UID);
    static QString getNormanWeightRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getNormanWeightRange(double a, double b);
    static QString getWeightAsOneNumberPlusMinus(long long uidCategory);
    static QString getNormanAgeRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getNormanAgeRange(int a, int b);


    static QString roundDouble(double x, int precision);

    static QString getTournamentNameAsHeadOfDocument(const QSqlDatabase& database, long long tournamentUID);
};

#endif // DBUTILS_H
