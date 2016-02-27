#include "db_utils.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <algorithm>
#include <utility>


QString DBUtils::getField(const QSqlDatabase& database, const QString& field, const QString& table, const QString& UID)
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toString();
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QString DBUtils::getField(const QSqlDatabase& database, const QString& field, const QString& table, const long long UID)
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toString();
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QString DBUtils::getFieldDate(const QSqlDatabase& database, const QString& field, const QString& table, const long long UID)
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toDate().toString("dd.MM.yyyy");
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QString DBUtils::getNameTournamentByUID(const QSqlDatabase& database, const long long UID)
{
    QSqlQuery query("SELECT NAME FROM TOURNAMENTS WHERE UID = ? ", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value("NAME").toString();
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QString DBUtils::getTypeNameByUID(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT NAME FROM TYPES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value("NAME").toString();
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QString DBUtils::get_SHORTNAME_FROM_SEXES(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT SHORTNAME FROM SEXES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value("SHORTNAME").toString();
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return "";
}

QStringList DBUtils::get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = ? ", database);
    query.bindValue(0, UID);
    QStringList res;
    if (query.exec() && query.next())
    {
        QDate dateBegin = query.value("DATE_BEGIN").toDate();
        QDate dateEnd = query.value("DATE_END").toDate();
        while (true)
        {
            res.push_back(dateBegin.toString("dd.MM.yyyy"));
            //qDebug() << dateBegin << dateEnd;
            if (dateBegin == dateEnd) break;
            dateBegin = dateBegin.addDays(1);
        }
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return res;
}

QString DBUtils::getSecondNameAndOneLetterOfName(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM ORDERS WHERE UID = ? ", database);
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("SECOND_NAME").toString() + " " +
              query.value("FIRST_NAME").toString().left(1) + ".";
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}


QString DBUtils::get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = ? ", database);
    query.bindValue(0, tournamentUID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("MAIN_JUDGE").toString();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

QString DBUtils::get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = ? ", database);
    query.bindValue(0, tournamentUID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("MAIN_SECRETARY").toString();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

QString DBUtils::get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = ? ", database);
    query.bindValue(0, tournamentUID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("ASSOCIATE_MAIN_JUDGE").toString();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}


QVector<DBUtils::NodeOfTournirGrid> DBUtils::getNodes(const QSqlDatabase& database, long long tournamentCategories)
{
    QVector<DBUtils::NodeOfTournirGrid> arr;

    QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
    query.bindValue(0, tournamentCategories);
    if (!query.exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        arr.clear();
        return arr;
    }
    while (query.next())
    {
        QString orderUID = query.value("ORDER_FK").toString();
        QString name = "Unknown";
        QString region = "";
        bool isFighing = query.value("IS_FIGHTING").toBool();
        if (orderUID.size() != 0)
        {
            QSqlQuery queryOrder("SELECT * FROM ORDERS WHERE UID = ? ", database);
            queryOrder.bindValue(0, orderUID);
            if (!(queryOrder.exec() && queryOrder.next()))
            {
                qDebug() << __PRETTY_FUNCTION__ << " " << queryOrder.lastError().text() << "\n" << queryOrder.lastQuery();
                qDebug() <<  "Нет такого orderUID" << orderUID;
                arr.clear();
                return arr;
            }
            //name = queryOrder.value("SECOND_NAME").toString() + " " + queryOrder.value("FIRST_NAME").toString();
            name = queryOrder.value("SECOND_NAME").toString();

            QSqlQuery queryRegion("SELECT * FROM REGIONS WHERE UID = ? ", database);
            //qDebug() << __PRETTY_FUNCTION__ << queryOrder.value("REGION_FK").toString();
            queryRegion.bindValue(0, queryOrder.value("REGION_FK").toString());
            if (!(queryRegion.exec() && queryRegion.next()))
            {
                qDebug() << __PRETTY_FUNCTION__ << " " << queryRegion.lastError().text() << "\n" << queryRegion.lastQuery();
                qDebug() <<  "Нет такого REGION_FK" << queryOrder.value("REGION_FK").toString();
                arr.clear();
                return arr;
            }
            region = queryRegion.value("SHORTNAME").toString();
        }
        arr.push_back(NodeOfTournirGrid({query.value("VERTEX").toInt(), name, region, isFighing, orderUID.toLongLong(), query.value("result").toString()}));
    }

    qSort(arr);
    return arr;
}

QVector<DBUtils::NodeOfTournirGrid> DBUtils::getLeafOFTree(const QSqlDatabase& database, long long tournamentCategories)
{
    QVector<DBUtils::NodeOfTournirGrid> res;
    for (DBUtils::NodeOfTournirGrid node : getNodes(database, tournamentCategories))
        if (!node.isFighing)
            res.push_back(node);
    if (!res.empty())
    {
        tournamentCategories = tournamentCategories;
    }

    std::random_shuffle(res.begin(), res.end());
    std::sort(std::begin(res), std::end(res), [database] (const DBUtils::NodeOfTournirGrid& lhs, const DBUtils::NodeOfTournirGrid& rhs) {
        return DBUtils::getSecondNameAndOneLetterOfName(database, lhs.UID) <
                DBUtils::getSecondNameAndOneLetterOfName(database, rhs.UID);
    });
    return res;
}

QVector<QVector<DBUtils::Fighing>> DBUtils::getListsOfPairs(const QSqlDatabase& database, long long tournamentUID)
{
    QVector<QVector<Fighing>> result;

    QSqlQuery query_TOURNAMENT_CATEGORIES("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ORDER BY TYPE_FK, AGE_FROM", database);
    query_TOURNAMENT_CATEGORIES.bindValue(0, tournamentUID);
    if (!query_TOURNAMENT_CATEGORIES.exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << query_TOURNAMENT_CATEGORIES.lastError().text() << query_TOURNAMENT_CATEGORIES.lastQuery();
        result.clear();
        return result;
    }
    while (query_TOURNAMENT_CATEGORIES.next())
    {
        long long TOURNAMENT_CATEGORIES_UID = query_TOURNAMENT_CATEGORIES.value("UID").toLongLong();

        QVector<Fighing> listOfPairs = getListOfPairs(database, TOURNAMENT_CATEGORIES_UID);
        if (listOfPairs.size())
            result.push_back(listOfPairs);
    }

    return result;
}

QVector<DBUtils::Fighing> DBUtils::getListOfPairs(const QSqlDatabase& database, long long tournamentCategory)
{
    QVector<Fighing> arr;
    QVector<NodeOfTournirGrid> nodes = getNodes(database, tournamentCategory);
    for (int i = nodes.size() - 1; 0 <= i; --i)
    {
        NodeOfTournirGrid node = nodes[i];
        //qDebug() << node.name;
        if (node.name == "Unknown")
        {
            arr.push_back(Fighing({
                                      nodes[2 * node.v + 1 - 1].UID,
                                      nodes[2 * node.v     - 1].UID,
                                      node.v,
                                      tournamentCategory,
                                      0
                                  }));
            if (isPow2(node.v))
                break;
        }
    }

    std::reverse(arr.begin(), arr.end());
    return arr;
}

bool DBUtils::setNodeOfGrid(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result)
{
    QSqlQuery query("UPDATE GRID     SET ORDER_FK = ? , result = ?     WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
    query.bindValue(0, orderUID);
    query.bindValue(1, result);
    query.bindValue(2, TOURNAMENT_CATEGORIES_FK);
    query.bindValue(3, VERTEX);
    return query.exec();
}

QVector<long long> DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long tournamentUID)
{
    QVector<long long> uids;
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ", database);
    query.bindValue(0, tournamentUID);
    if (!query.exec())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    else
        while(query.next())
            uids.push_back(query.value("UID").toLongLong());
    //qDebug() << uids;
    return uids;
}

QString DBUtils::get__NAME_OF_TOURNAMENT_CATEGORIES(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("NAME").toString();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}


QVector<std::tuple<long long, int, int, long long> > DBUtils::get_distinct_TYPE_FK_AgeFrom_AgeTill(const QSqlDatabase& database, long long tournamentUID)
{
    QVector<std::tuple<long long, int, int, long long> > res;
    QSqlQuery query("SELECT DISTINCT TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ORDER BY TYPE_FK, AGE_TILL, SEX_FK", database);
    query.bindValue(0, tournamentUID);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
        return res;
    }
    while (query.next())
    {
        res << std::make_tuple(query.value("TYPE_FK").toLongLong(), query.value("AGE_FROM").toInt(), query.value("AGE_TILL").toInt(), query.value("SEX_FK").toLongLong());
    }
    return res;
}

QMap<QString, QVector<long long> > DBUtils::get_weight_and_orderUIDs(const QSqlDatabase& database,
                                                                     long long tournamentUID, long long TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK)
{
    QMap<QString, QVector<long long> > res;
    QSqlQuery query("SELECT UID FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? AND AGE_TILL = ? AND SEX_FK = ? ORDER BY WEIGHT_FROM, WEIGHT_TILL", database);
    query.bindValue(0, tournamentUID);
    query.bindValue(1, TYPE_FK);
    query.bindValue(2, AGE_FROM);
    query.bindValue(3, AGE_TILL);
    query.bindValue(4, SEX_FK);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
        return res;
    }
    while (query.next())
    {

        long long uidCategory = query.value("UID").toLongLong();
        QString WEIGHT_FROM = getField(database, "WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidCategory);
        QString WEIGHT_TILL = getField(database, "WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidCategory);

        QVector<NodeOfTournirGrid> nodes = getNodes(database, uidCategory);
        for (int iter = 0; iter < 4 && !nodes.empty(); ++iter)
        {
            long long orderUID = nodes[0].UID;
            res[WEIGHT_FROM + " - " + WEIGHT_TILL].push_back(orderUID);
            for (int i = 0; i < nodes.size(); ++i)
                while (i < nodes.size() && nodes[i].UID == orderUID)
                    nodes.remove(i);
        }
    }
    return res;
}



int DBUtils::get__DURATION_FIGHING(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    int res = 0;
    if (query.exec() && query.next())
        res = query.value("DURATION_FIGHING").toInt();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

int DBUtils::get__DURATION_BREAK(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    int res = 0;
    if (query.exec() && query.next())
        res = query.value("DURATION_BREAK").toInt();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

int DBUtils::get__ROUND_COUNT(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    int res = 0;
    if (query.exec() && query.next())
        res = query.value("ROUND_COUNT").toInt();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

int DBUtils::get__AGE_FROM(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    int age = 0;
    if (query.exec() && query.next())
        age = query.value("AGE_FROM").toInt();
    return age;
}

int DBUtils::get__AGE_TILL(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    int age = 0;
    if (query.exec() && query.next())
        age = query.value("AGE_TILL").toInt();
    return age;
}

QString DBUtils::get__WEIGHT_FROM(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("WEIGHT_FROM").toString();
    return res;
}

QString DBUtils::get__WEIGHT_TILL(const QSqlDatabase& database, long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ? ", database);
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("WEIGHT_TILL").toString();
    return res;
}