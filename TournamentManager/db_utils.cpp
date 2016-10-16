#include "db_utils.h"
#include "renderareawidget.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <algorithm>
#include <utility>




QString DBUtils::getField(const QString& field, const QString& table, const QString& UID, QString )
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?");
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toString();
    }
    else
    {
        //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << PRETTY_FUNCTION << query.lastError()<< query.lastQuery() << "  UID:" << UID << " field:" << field;
    }
    return "";
}

QString DBUtils::getField(const QString& field, const QString& table, const long long UID, QString )
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?");
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toString();
    }
    else
    {
        //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << PRETTY_FUNCTION << query.lastError()<< query.lastQuery() << "  UID:" << UID << " field:" << field;
    }
    return "";
}

QString DBUtils::getFieldDate(const QString& field, const QString& table, const long long UID, QString )
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?");
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toDate().toString("dd.MM.yyyy");
    }
    else
    {
        //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << PRETTY_FUNCTION << query.lastError()<< query.lastQuery() << "  UID:" << UID;
    }
    return "";
}

QDate DBUtils::getFieldDateAsDate(const QString& field, const QString& table, const long long UID)
{
    QSqlQuery query("SELECT * FROM " + table + " WHERE UID = ?");
    query.bindValue(0, UID);
    if (query.exec() && query.next())
    {
        return query.value(field).toDate();
    }
    else
    {
        //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    }
    return QDate();
}


QStringList DBUtils::get_DAYS_FROM_TOURNAMENTS(long long UID)
{
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = ? ");
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

QString DBUtils::getSecondNameAndFirstName(long long UID)
{
    QSqlQuery query("SELECT * FROM ORDERS WHERE UID = ? ");
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("SECOND_NAME").toString() + " " +
              query.value("FIRST_NAME").toString();
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery() << " UID: " << UID;
    return res;
}

QString DBUtils::getSecondNameAndOneLetterOfName(long long UID)
{
    QSqlQuery query("SELECT * FROM ORDERS WHERE UID = ? ");
    query.bindValue(0, UID);
    QString res;
    if (query.exec() && query.next())
        res = query.value("SECOND_NAME").toString() + " " +
              query.value("FIRST_NAME").toString().left(1) + ".";
    else
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    return res;
}

QSet<long long> DBUtils::getSetOfOrdersInTournamentCategory(long long uidTournamentCategory)
{
    QSet<long long> set;
    QSqlQuery queryOrder("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ");
    queryOrder.addBindValue(uidTournamentCategory);
    if (!queryOrder.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryOrder.lastError() << queryOrder.lastQuery();
    }
    while (queryOrder.next())
    {
        set << queryOrder.value("UID").toLongLong();
    }
    return set;
}

int DBUtils::getAge(QDate DATE_WEIGHTING, QDate birthdayDate)
{
    int age = DATE_WEIGHTING.year() - birthdayDate.year();
    if ( DATE_WEIGHTING.month() <  birthdayDate.month() ||
        (DATE_WEIGHTING.month() == birthdayDate.month() && DATE_WEIGHTING.day() < birthdayDate.day()))
    {
        --age;
    }
    return age;
}

QVector<QString> DBUtils::getJudges(long long tournamentUID)
{
    return QVector<QString>()
            << DBUtils::getField("MAIN_JUDGE"          , "TOURNAMENTS", tournamentUID)
            << DBUtils::getField("MAIN_SECRETARY"      , "TOURNAMENTS", tournamentUID)
            << DBUtils::getField("ASSOCIATE_MAIN_JUDGE", "TOURNAMENTS", tournamentUID);
}

QVector<std::tuple<int, int, int, int> > DBUtils::get_MAX_UID_TC___TYPE_FK___AGE_FROM___AGE_TILL(const int tournamentUID)
{
    QSqlQuery query("SELECT MAX(UID) as MAX_UID_TC, TYPE_FK, AGE_FROM, AGE_TILL "
                                    "FROM TOURNAMENT_CATEGORIES "
                                    "WHERE TOURNAMENT_FK = ? "
                                    "GROUP BY TYPE_FK, AGE_FROM, AGE_TILL "
                                    "ORDER BY TYPE_FK, AGE_FROM, AGE_TILL");
    query.addBindValue(tournamentUID);
    if (!query.exec())
    {
        qDebug() << "Fuck";
    }
    QVector<std::tuple<int, int, int, int> > result;
    while (query.next()){
        result << std::make_tuple(
                      query.value("MAX_UID_TC").toInt(),
                      query.value("TYPE_FK").toInt(),
                      query.value("AGE_FROM").toInt(),
                      query.value("AGE_TILL").toInt()
                      );
    }
    return result;
}

QSqlQuery * DBUtils::get___AGE_CATEGORY_FK___SEX_FK(int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL)
{
    QSqlQuery * q = new QSqlQuery;
    q->prepare("SELECT AGE_CATEGORY_FK, SEX_FK "
              "FROM TOURNAMENT_CATEGORIES "
              "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? AND AGE_TILL = ? "
              "GROUP BY AGE_CATEGORY_FK, SEX_FK "
              "ORDER BY SEX_FK");
    q->addBindValue(tournamentUID);
    q->addBindValue(TYPE_FK);
    q->addBindValue(AGE_FROM);
    q->addBindValue(AGE_TILL);
    if (q->lastError().isValid())
        qDebug() << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << q->lastError();

    return q;
}

QSqlQuery * DBUtils::get___WEIGHT_FROM___WEIGHT_TILL(int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK, int ageCatUID)
{
    QSqlQuery * q = new QSqlQuery;
    q->prepare(
                "SELECT UID AS UID_TC, WEIGHT_FROM, WEIGHT_TILL "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ?  AND AGE_FROM = ? AND AGE_TILL = ? AND SEX_FK = ? AND AGE_CATEGORY_FK = ? "
                "GROUP BY WEIGHT_FROM, WEIGHT_TILL "
                "ORDER BY WEIGHT_FROM, WEIGHT_TILL"
              );
    q->addBindValue(tournamentUID);
    q->addBindValue(TYPE_FK);
    q->addBindValue(AGE_FROM);
    q->addBindValue(AGE_TILL);
    q->addBindValue(SEX_FK);
    q->addBindValue(ageCatUID);
    if (q->lastError().isValid())
        qDebug() << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << q->lastError();

    return q;
}

QSqlQuery*DBUtils::get___TC_UIDS(int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK, int ageCatUID, int WEIGHT_FROM, int WEIGHT_TILL)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
                "SELECT UID "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE "
                "   TOURNAMENT_FK = ? AND "
                "   TYPE_FK = ?  AND "
                "   AGE_FROM = ? AND "
                "   AGE_TILL = ? AND "
                "   SEX_FK = ? AND "
                "   AGE_CATEGORY_FK = ? AND "
                "   WEIGHT_FROM = ? AND "
                "   WEIGHT_TILL = ? "
                )){
        qDebug() << q->lastError();
    }
    q->addBindValue(tournamentUID);
    q->addBindValue(TYPE_FK);
    q->addBindValue(AGE_FROM);
    q->addBindValue(AGE_TILL);
    q->addBindValue(SEX_FK);
    q->addBindValue(ageCatUID);
    q->addBindValue(WEIGHT_FROM);
    q->addBindValue(WEIGHT_TILL);
    if (q->lastError().isValid())
        qDebug() << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << q->lastError();

    return q;
}


QVector<DBUtils::NodeOfTournirGrid> DBUtils::getNodes(long long tournamentCategories)
{
    QVector<DBUtils::NodeOfTournirGrid> arr;

    QSqlQuery query(
                "SELECT * "
                "FROM GRID "
                "WHERE TOURNAMENT_CATEGORIES_FK = ? "
                "ORDER BY VERTEX");
    query.addBindValue(tournamentCategories);
    if (!query.exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << query.lastQuery();
        return arr;
    }
    while (query.next())
    {
        QString orderUID = query.value("ORDER_FK").toString();
        bool isFighing = query.value("IS_FIGHTING").toBool();
        QString name = "_________";
        QString region = "";
        if (!orderUID.isEmpty())
        {
            name   = DBUtils::getField("SECOND_NAME", "ORDERS", orderUID, __PRETTY_FUNCTION__) +  " " +
                     DBUtils::getField("FIRST_NAME" , "ORDERS", orderUID, __PRETTY_FUNCTION__);
            region =
                    DBUtils::getField("NAME", "COUNTRIES", DBUtils::getField("COUNTRY_FK", "ORDERS", orderUID, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__) +
                    " / " +
                    DBUtils::getField("NAME", "REGIONS"  , DBUtils::getField("REGION_FK" , "ORDERS", orderUID, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        NodeOfTournirGrid node = NodeOfTournirGrid(
                                     tournamentCategories,
                                     query.value("VERTEX").toInt(),
                                     isFighing,
                                     orderUID.toLongLong(),
                                     query.value("result").toString(),
                                     query.value("DAY_FIGHT").toInt(),
                                     query.value("TIME_FIGHT").toInt()
                                     );
        node.name   = name;
        node.region = region;

        arr << node;
    }
    for (int v = 1; v <= arr.size(); ++v)
    {
        if (arr[v - 1].isFight)
        {
            arr[v - 1].leftUID   = arr[2 * v + 1 - 1].UID;
            arr[v - 1].leftName  = arr[2 * v + 1 - 1].name;

            arr[v - 1].rightUID  = arr[2 * v     - 1].UID;
            arr[v - 1].rightName = arr[2 * v     - 1].name;
        }
    }
    return arr;
}

QSqlQuery* DBUtils::getFightNodes(int tournamentCategoryUID)
{
    QSqlQuery * query = new QSqlQuery(
                "SELECT * "
                "FROM GRID "
                "WHERE TOURNAMENT_CATEGORIES_FK = ? AND IS_FIGHTING = 1 ");
    query->addBindValue(tournamentCategoryUID);
    if (!query->exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << query->lastQuery();
    }
    return query;
}

//int DBUtils::f(int tournamentCategoryUID, int day, int time)
//{
//    QSqlQuery * query = new QSqlQuery(
//                "SELECT COUNT(*) AS cnt "
//                "FROM GRID "
//                "WHERE "
//                "   TOURNAMENT_CATEGORIES_FK = ? AND "
//                "   IS_FIGHTING = 1 AND "
//                "   ORDER_FK <= 0 AND "
//                "   DAY_FIGHT = ? AND "
//                "   TIME_FIGHT = ? "
//                "GROUP BY DAY_FIGHT, TIME_FIGHT ");
//    query->addBindValue(tournamentCategoryUID);
//    query->addBindValue(day);
//    query->addBindValue(time);
//    if (!query->exec())
//    {
//        qDebug() << __PRETTY_FUNCTION__ << query->lastQuery();
//    }
//    int cnt = 0;
//    if (query->next())
//    {
//        cnt = query->value("cnt").toInt();
//    }
//    return cnt;
//}

//QSqlQuery*DBUtils::ff(int tournamentCategoryUID)
//{
//    QSqlQuery * query = new QSqlQuery;
//    if (!query->prepare(
//                "SELECT COUNT(*) AS cnt, DAY_FIGHT, TIME_FIGHT "
//                "FROM GRID "
//                "WHERE "
//                "   TOURNAMENT_CATEGORIES_FK = ? AND "
//                "   IS_FIGHTING = 1 AND "
//                "   ORDER_FK <= 0 AND "
//                "GROUP BY DAY_FIGHT, TIME_FIGHT "
//                "ORDER BY DAY_FIGHT, TIME_FIGHT "))
//        qDebug() << query->lastError();
//    query->addBindValue(tournamentCategoryUID);
//    if (!query->exec())
//    {
//        qDebug() << query->lastError();
//    }
//    return query;
//}

QVector<QVector<DBUtils::NodeOfTournirGrid> > DBUtils::getNodesAsLevelListOfList(long long tournamentCategoryUID)
{
    QVector<QVector<DBUtils::NodeOfTournirGrid> > result;
    for(DBUtils::NodeOfTournirGrid node : DBUtils::getNodes(tournamentCategoryUID))
    {
        if (result.size() == 0 || RenderAreaWidget::log2(result.back().last().v) != RenderAreaWidget::log2(node.v))
        {
            result << QVector<DBUtils::NodeOfTournirGrid>();
        }
        result.back() << node;
    }
    return result;
}

QVector<DBUtils::NodeOfTournirGrid> DBUtils::getLeafOFTree(long long tournamentCategories)
{
    QVector<DBUtils::NodeOfTournirGrid> res;
    for (DBUtils::NodeOfTournirGrid node : getNodes(tournamentCategories))
        if (!node.isFight)
            res.push_back(node);
    if (!res.empty())
    {
        tournamentCategories = tournamentCategories;
    }

    std::random_shuffle(res.begin(), res.end());
    std::sort(std::begin(res), std::end(res), [] (const DBUtils::NodeOfTournirGrid& lhs, const DBUtils::NodeOfTournirGrid& rhs) {
        return DBUtils::getSecondNameAndOneLetterOfName(lhs.UID) <
                DBUtils::getSecondNameAndOneLetterOfName(rhs.UID);
    });
    return res;
}

QVector<DBUtils::NodeOfTournirGrid> DBUtils::getFightingNodes(long long tournamentCategoryUID)
{
    QVector<DBUtils::NodeOfTournirGrid> res;
    for(NodeOfTournirGrid f : getNodes(tournamentCategoryUID))
        if (f.isFight)
            res << f;
    return res;
}

void DBUtils::insertLeafOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID)
{
    QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?,    ?, ?,    ?, ?) ");
    query.addBindValue(TOURNAMENT_CATEGORIES_FK);
    query.addBindValue(VERTEX);
    query.addBindValue(0);

    query.addBindValue(orderUID);
    query.addBindValue("");

    query.addBindValue(-1);
    query.addBindValue(-1);
    if (!query.exec())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
}

bool DBUtils::insertResultOfFightForNodeOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result)
{
    QSqlQuery query("UPDATE GRID "
                    "SET ORDER_FK = ? , result = ? "
                    "WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
    query.addBindValue(orderUID);
    query.addBindValue(result);
    query.addBindValue(TOURNAMENT_CATEGORIES_FK);
    query.addBindValue(VERTEX);
    return query.exec();
}

void DBUtils::swapNodesOfGrid(long long tournamentCategories, int node0v, int node1v)
{
    {
        QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
        query.bindValue(0, 100500);
        query.bindValue(1, tournamentCategories);
        query.bindValue(2, node0v);
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
    }
    {
        QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
        query.bindValue(0, node0v);
        query.bindValue(1, tournamentCategories);
        query.bindValue(2, node1v);
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
    }
    {
        QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
        query.bindValue(0, node1v);
        query.bindValue(1, tournamentCategories);
        query.bindValue(2, 100500);
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
    }
}

int DBUtils::getDurationOfGrid(long long tournamentCategories, int delay)
{
    int time = 0;
    for (const DBUtils::NodeOfTournirGrid f : DBUtils::getNodes(tournamentCategories))
    {
        if (!f.isFight) continue;
        time += DBUtils::getDurationOfFightinPair(tournamentCategories) + delay;
    }
    return time;
}

int DBUtils::getDurationOfFightinPair(long long tournamentCategories)
{
    int count = DBUtils::getField("ROUND_COUNT", "TOURNAMENT_CATEGORIES", tournamentCategories).toInt();
    return
        count * DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", tournamentCategories).toInt()
        +
            (count - 1) * DBUtils::getField("DURATION_BREAK", "TOURNAMENT_CATEGORIES", tournamentCategories).toInt();
}

std::pair<int, int> DBUtils::getPlace(long long UIDOrder)
{
    long long tournamentCategoryUID = getField("TOURNAMENT_CATEGORY_FK", "ORDERS", UIDOrder).toLongLong();
    QVector<QVector<NodeOfTournirGrid> > grid = getNodesAsLevelListOfList(tournamentCategoryUID);

//    qDebug() << "DBUtils::getPlace";
//    for (int i = 0; i < grid.size(); ++i)
//    {
//        QString str;
//        for (int j = 0; j < grid[i].size(); ++j)
//        {
//            str += (j == 0 ? "" : " ") + QString::number(grid[i][j].v);
//        }
//        qDebug() << str;
//    }
//    qDebug() << "=================";

    int countPlayers = 0;
    for (int i = 0, r = 1; i < grid.size(); ++i, r *= 2)
    {
        countPlayers += grid[i].size();
        for (int j = 0; j < grid[i].size(); ++j)
        {
            NodeOfTournirGrid node = grid[i][j];
            if (node.UID == UIDOrder)
            {
                return 0 <= i - 1 && grid[i - 1][j / 2].UID <= 0?
                        std::make_pair(-1, -1) :
                        std::make_pair(r / 2 + 1, std::min(r, countPlayers));
            }
        }
    }
    return std::make_pair(-1, -1);
}

QVector<std::pair<long long, std::pair<int, int>>> DBUtils::getUIDsAndPlaces(long long tournamentCategoryUID, int maxPlace, bool skeepEmptyGrids)
{
    QVector<QVector<NodeOfTournirGrid> > grid = getNodesAsLevelListOfList(tournamentCategoryUID);
    QVector<std::pair<long long, std::pair<int, int>>> result;
    QSet<long long> used;
    for (int i = 0, r = 1; i < grid.size(); ++i, r *= 2)
    {
        if (maxPlace < r)
            break;
        for (int j = 0; j < grid[i].size(); ++j)
        {
            NodeOfTournirGrid node = grid[i][j];
            if (node.UID <= 0)
            {
                if (skeepEmptyGrids)
                {
                    result.clear();
                    return result;
                }
            }
            else if (!used.contains(node.UID))
            {
                used  << node.UID;
                result << std::make_pair(
                              node.UID,
                              0 <= i - 1 && grid[i - 1][j / 2].UID <= 0?
                              std::make_pair(-1, -1) :
                              std::make_pair(r / 2 + 1, r)
                              );
            }
        }
    }
    return result;
}

int DBUtils::getNumberOfCastingOfLots(long long uidOrder)
{
    long long uidTC = getField("TOURNAMENT_CATEGORY_FK", "ORDERS", uidOrder).toLongLong();

    QSqlQuery query;

    if (!query.prepare("SELECT VERTEX FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? AND ORDER_FK = ? AND IS_FIGHTING = \"false\""))
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        return -1;
    }
    query.addBindValue(uidTC);
    query.addBindValue(uidOrder);
    if (!query.exec() || !query.next())
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        return -1;
    }

    int v = query.value("VERTEX").toInt();


    query.clear();
    if (!query.prepare("SELECT MAX(VERTEX) AS maxVertex FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ?"))
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        return -1;
    }
    query.addBindValue(uidTC);
    if (!query.exec() || !query.next())
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        return -1;
    }
    int maxVertex = query.value("maxVertex").toInt();


//    QVector<NodeOfTournirGrid> leafOFTree = DBUtils::getLeafOFTree(uidTC);
//    int maxVertex = 1;
//    int v = -1;
//    for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree)
//    {
//        maxVertex = qMax(maxVertex, leaf.v); // TOO SLOW
//        if (leaf.UID == uidOrder)
//        {
//            v = leaf.v;
//        }
//    }
    return maxVertex - v + 1;
}

bool DBUtils::updateLevelOfNodeOfGrid(int TOURNAMENT_CATEGORIES_FK, int VERTEX, int DAY_FIGHT, int TIME_FIGHT)
{
    QSqlQuery query("UPDATE GRID "
                    "SET DAY_FIGHT = ?, TIME_FIGHT = ? "
                    "WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
    query.addBindValue(DAY_FIGHT);
    query.addBindValue(TIME_FIGHT);
    query.addBindValue(TOURNAMENT_CATEGORIES_FK);
    query.addBindValue(VERTEX);
    return query.exec();
}

QVector<long long> DBUtils::get_UIDOrder_for_TC(long long UIDtournamentCategory)
{
    QSet<long long> set;
    for (auto node : getNodes(UIDtournamentCategory))
        if (0 < node.UID)
            set << node.UID;
    QVector<long long> result;
    for (long long uid : set)
        result << uid;
    return result;
}

QVector<long long> DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(long long tournamentUID)
{
    QVector<long long> uids;
    QSqlQuery query(
                "SELECT * "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE TOURNAMENT_FK = ? "
                "ORDER BY AGE_FROM, AGE_TILL, TYPE_FK, SEX_FK, WEIGHT_FROM, WEIGHT_TILL");
    query.addBindValue(tournamentUID);
    if (!query.exec())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
    else
        while(query.next())
            uids.push_back(query.value("UID").toLongLong());
    //qDebug() << uids;
    return uids;
}


QVector<std::tuple<long long, int, int, long long> > DBUtils::get_distinct_TYPE_FK_AgeFrom_AgeTill(long long tournamentUID)
{
    QVector<std::tuple<long long, int, int, long long> > res;
    QSqlQuery query("SELECT DISTINCT TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ORDER BY TYPE_FK, AGE_TILL, SEX_FK");
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

QMap<QString, QVector<long long> > DBUtils::get_weight_and_orderUIDs(long long tournamentUID, long long TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK, int maxPlace)
{
    QMap<QString, QVector<long long> > res;
    QSqlQuery query("SELECT UID "
                    "FROM TOURNAMENT_CATEGORIES "
                    "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? AND AGE_TILL = ? AND SEX_FK = ? "
                    "ORDER BY WEIGHT_FROM, WEIGHT_TILL");
    query.addBindValue(tournamentUID);
    query.addBindValue(TYPE_FK);
    query.addBindValue(AGE_FROM);
    query.addBindValue(AGE_TILL);
    query.addBindValue(SEX_FK);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
        return res;
    }
    while (query.next())
    {

        long long uidCategory = query.value("UID").toLongLong();
        QString weight = DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", uidCategory);

        QVector<NodeOfTournirGrid> nodes = getNodes(uidCategory);
        QSet<long long> used;
        int place = 0;
        for (int i = 0; i < nodes.size(); ++i)
        {
            long long orderUID = nodes[i].UID;
            if (orderUID == 0)
                break;
            if (used.contains(orderUID))
                continue;

            ++place;
            if (maxPlace < place)
                break;

            used << orderUID;
            res[weight].push_back(orderUID);
        }
    }
    return res;
}



QString DBUtils::getWeightAsOneNumberPlusMinus(long long uidCategory)
{
    double from = DBUtils::getField("WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidCategory).toDouble();
    double till = DBUtils::getField("WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidCategory).toDouble();
    if (qAbs(from) < 1e-7)
        return "-" + DBUtils::roundDouble(till, 2);
    else if (200 - 1e-7 <= till)
        return "+" + DBUtils::roundDouble(from, 2);
    return DBUtils::roundDouble(till, 2);
}

QString DBUtils::getNormanAgeRangeFromTOURNAMENT_CATEGORIES(long long uidCategory)
{
    return DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", uidCategory);
}

QString DBUtils::getNameForExcelSheet(long long uidTC)
{
    QString sheetName = DBUtils::getField("SHORTNAME", "SEXES", DBUtils::getField("SEX_FK", "TOURNAMENT_CATEGORIES", uidTC)) +
                        ", " +
                        DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", uidTC) +
                        " ," +
                        DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", uidTC) +
                        ", " +
                        DBUtils::getField("NAME", "TYPES", DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidTC));
    return sheetName.left(31);
}

int DBUtils::getMaxDayFromGrids(long long tournamentUID)
{
    QSqlQuery q;
    q.prepare(
                "SELECT MAX(DAY_FIGHT) AS MAXDAY "
                "FROM GRID A "
                "   LEFT JOIN TOURNAMENT_CATEGORIES B "
                "       ON A.TOURNAMENT_CATEGORIES_FK = B.UID "
                "WHERE TOURNAMENT_FK = ? "
    );
    q.addBindValue(tournamentUID);
    if (q.lastError().isValid())
        qDebug() << q.lastError();
    q.exec();
    if (q.lastError().isValid())
        qDebug() << q.lastError();
    int maxCountDays = 0;
    if (q.next()){
        maxCountDays = q.value("MAXDAY").toInt() + 1; // нумерация с дней с нуля
        //qDebug() << "maxCountDays: " << maxCountDays;
    }
    return maxCountDays;
}

QSqlQuery*DBUtils::get___TYPE_FK___AGE_FROM___AGE_TILL(const int RING_TATAMI_LIST_FK)
{
    QSqlQuery* q = new QSqlQuery;
    q->prepare("SELECT MAX(B.UID) AS MAX_UID_TC, B.TYPE_FK, B.AGE_FROM, B.AGE_TILL "
              "FROM RING_TATAMI_LISTS_DATA A "
              "   LEFT JOIN TOURNAMENT_CATEGORIES B "
              "      on A.TYPE_FK = B.TYPE_FK AND A.AGE_FROM = B.AGE_FROM AND A.AGE_TILL = B.AGE_TILL "
              "WHERE RING_TATAMI_LIST_FK = ? "
              "GROUP BY A.TYPE_FK, A.AGE_FROM, A.AGE_TILL "
              "ORDER BY A.TYPE_FK, A.AGE_FROM, A.AGE_TILL "
              );
    q->addBindValue(RING_TATAMI_LIST_FK);
    if (q->lastError().isValid())
        qDebug() << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << q->lastError();

    return q;
}



QString DBUtils::roundDouble(double x, int precision)
{
    QString res = QString::number(x, 'f', precision);
    res.remove( QRegExp("0+$") ); // Remove any number of trailing 0's
    res.remove( QRegExp("\\.$") ); // If the last character is just a '.' then remove it
    return res;
}


QString DBUtils::toString(std::pair<DBUtils::TypeField, QString> pair)
    {
    QString res = getExplanationOfTypeField()[pair.first];
    if (pair.first == TypeField::PlainText)
        res += " \"" + pair.second + "\"";
    return res;
}

QString DBUtils::toString(QVector<std::pair<DBUtils::TypeField, QString> > vector){
    QString res;
    for (std::pair<TypeField, QString> pair : vector){
        if (!res.isEmpty())
            res += "; ";
        res += toString(pair);
    }
    return res;
}

QString DBUtils::getTournamentNameAsHeadOfDocument(long long tournamentUID)
{
//    QDate a = DBUtils::getFieldDateAsDate("DATE_WEIGHTING", "TOURNAMENTS", tournamentUID);
//    QDate b = DBUtils::getFieldDateAsDate("DATE_END", "TOURNAMENTS", tournamentUID);
//    QString resA;
//    QString resB = QString::number(b.day()) + " " + getRussianMonth(b.month()) + " " + QString::number(b.year()) + " г.";
//    if (a.year() != b.year())
//    {
//        resA = QString::number(a.day()) + " " + getRussianMonth(a.month()) + " " + QString::number(a.year()) + " - ";
//    }
//    else if (a.month() != b.month())
//    {
//        resA = QString::number(a.day()) + " " + getRussianMonth(a.month()) + " - ";
//    }
//    else if (a.day() != b.day())
//    {
//        resA = QString::number(a.day()) + "-";
//    }
//    else
//    {
//        resA = "";
//    }
    return DBUtils::getField("NAME"          , "TOURNAMENTS", tournamentUID) + "\n" +
           DBUtils::getField("HOST"          , "TOURNAMENTS", tournamentUID) + ", " +
           DBUtils::getField("TEXT_DAT_RANGE", "TOURNAMENTS", tournamentUID);

}

QString DBUtils::convertToRoman(int val) {
    if (val <= 0) return QString::number(val);

    QString res;

    QStringList huns({"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"});
    QStringList tens({"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"});
    QStringList ones({"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"});

    while (val >= 1000) {
        res += "M";
        val -= 1000;
    }

    res += huns[val / 100];
    val %= 100;

    res += tens[val / 10];
    val %= 10;

    res += ones[val];

    return res;
}

int DBUtils::isPow2(int a) { return !(a & (a - 1)); }
