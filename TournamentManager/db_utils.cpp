#include "db_utils.h"


QVariant DBUtils::get(const QString& field, const QString& table, const QVariant& UID)
{
    QSqlQuery query("SELECT " + field + " FROM " + table + " WHERE UID = ?");
    query.addBindValue(UID);
    if (!query.exec())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError()<< query.lastQuery();
    if (query.next())
    {
        return query.value(field);
    }
    return QVariant();
}

bool DBUtils::set(const QString& field, const QString& table, const QVariant& UID, const QVariant& value)
{
    QSqlQuery query("UPDATE " + table + " "
                    "SET " + field + " = ? "
                    "WHERE UID = ?");
    query.addBindValue(value);
    query.addBindValue(UID);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError()<< query.lastQuery();
        return false;
    }
    return true;
}

QString DBUtils::getField(const QString& field, const QString& table, const QString& UID, QString )
{
    return get(field, table, UID).toString();
}

QString DBUtils::getField(const QString& field, const QString& table, const long long UID, QString )
{
    return get(field, table, UID).toString();
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
    {
        //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery() << " UID: " << UID;
    }
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

QVector<int> DBUtils::getOrderUIDsInTournamentCategory(long long uidTournamentCategory)
{
    QVector<int> set;
    QSqlQuery queryOrder("SELECT * "
                         "FROM ORDERS "
                         "WHERE TOURNAMENT_CATEGORY_FK = ? "
                         "ORDER BY "
                         "    SECOND_NAME, FIRST_NAME");
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

int DBUtils::findUidToutnamentCategory(int tournamentUID, QDate birthday, int sexUID, double weight, int typeUID)
{
    int age = Utils::getAge(birthday, DBUtils::get("DATE_WEIGHTING", "TOURNAMENTS", tournamentUID).toDate());
    QSqlQuery query;
    if (!query.prepare("SELECT * "
                       "FROM TOURNAMENT_CATEGORIES "
                       "WHERE "
                       "    TOURNAMENT_FK = ? AND "
                       "    TYPE_FK = ? AND "
                       "    SEX_FK = ? AND "
                       "    AGE_FROM <= ? AND ? <= AGE_TILL AND "
                       "    WEIGHT_FROM + 1e-7 < ? AND ? < WEIGHT_TILL + 1e-7 "
                       ))
    {
        qDebug() << query.lastError();
        return -1;
    }
    query.addBindValue(tournamentUID);
    query.addBindValue(typeUID);
    query.addBindValue(sexUID);
    query.addBindValue(age);
    query.addBindValue(age);
    query.addBindValue(weight);
    query.addBindValue(weight);

    //qDebug() << tournamentUID << birthday << sexUID << weight << typeUID;

    if (!query.exec())
    {
        qDebug() << query.lastError();
        return -1;
    }
    if (query.next())
    {
        return query.value("UID").toInt();
    }
    return -1;
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
                "FROM GRIDS "
                "WHERE TOURNAMENT_CATEGORIES_FK = ? "
                "ORDER BY VERTEX");
    query.addBindValue(tournamentCategories);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return arr;
    }
    while (query.next())
    {
        int orderUID = query.value("ORDER_FK").toInt();
        bool isFighing = query.value("IS_FIGHTING").toBool();
        arr << NodeOfTournirGrid(
                    tournamentCategories,
                    query.value("VERTEX").toInt(),
                    isFighing,
                    orderUID,
                    query.value("result").toString(),
                    query.value("DAY_FIGHT").toInt(),
                    query.value("TIME_FIGHT").toInt()
                    );
    }
    return arr;
}

QSqlQuery* DBUtils::getFightNodes(int tournamentCategoryUID)
{
    QSqlQuery * query = new QSqlQuery(
                "SELECT * "
                "FROM GRIDS "
                "WHERE TOURNAMENT_CATEGORIES_FK = ? AND IS_FIGHTING = 1 ");
    query->addBindValue(tournamentCategoryUID);
    if (!query->exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << query->lastQuery();
    }
    return query;
}

QVector<QVector<DBUtils::NodeOfTournirGrid> > DBUtils::getNodesAsLevelListOfList(long long tournamentCategoryUID)
{
    QVector<QVector<DBUtils::NodeOfTournirGrid> > result;
    for(DBUtils::NodeOfTournirGrid node : DBUtils::getNodes(tournamentCategoryUID))
    {
        if (result.size() == 0 || Utils::log2(result.back().last().v) != Utils::log2(node.v))
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
    QSqlQuery query("INSERT INTO GRIDS VALUES (?, ?, ?,    ?, ?,    ?, ?) ");
    query.addBindValue(TOURNAMENT_CATEGORIES_FK);
    query.addBindValue(VERTEX);
    query.addBindValue(0);

    query.addBindValue(orderUID);
    query.addBindValue(QVariant());

    query.addBindValue(-1);
    query.addBindValue(-1);
    if (!query.exec())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
}

bool DBUtils::insertResultOfFightForNodeOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result)
{
    QSqlQuery query("UPDATE GRIDS "
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
        QSqlQuery query("UPDATE GRIDS SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
        query.bindValue(0, 100500);
        query.bindValue(1, tournamentCategories);
        query.bindValue(2, node0v);
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
    }
    {
        QSqlQuery query("UPDATE GRIDS SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
        query.bindValue(0, node0v);
        query.bindValue(1, tournamentCategories);
        query.bindValue(2, node1v);
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
    }
    {
        QSqlQuery query("UPDATE GRIDS SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
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

QVector<std::pair<long long, std::pair<int, int>>> DBUtils::getUIDsAndPlaces(
        long long tournamentCategoryUID,
        int maxPlace,
        bool skeepEmptyGrids)
{
    QVector<std::pair<long long, std::pair<int, int>>> result;
    QVector<QVector<NodeOfTournirGrid> > grid = getNodesAsLevelListOfList(tournamentCategoryUID);
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

    if (!query.prepare("SELECT VERTEX "
                       "FROM GRIDS "
                       "WHERE "
                       "    TOURNAMENT_CATEGORIES_FK = ? AND "
                       "    ORDER_FK = ? AND "
                       "    IS_FIGHTING = 0"))
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
    if (!query.prepare("SELECT MAX(VERTEX) AS maxVertex FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ?"))
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

    return maxVertex - v + 1;
}

bool DBUtils::updateLevelOfNodeOfGrid(int TOURNAMENT_CATEGORIES_FK, int VERTEX, int DAY_FIGHT, int TIME_FIGHT)
{
    QSqlQuery query("UPDATE GRIDS "
                    "SET DAY_FIGHT = ?, TIME_FIGHT = ? "
                    "WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
    query.addBindValue(DAY_FIGHT);
    query.addBindValue(TIME_FIGHT);
    query.addBindValue(TOURNAMENT_CATEGORIES_FK);
    query.addBindValue(VERTEX);
    return query.exec();
}

void DBUtils::deleteGrid(const int tournamentCategoryUID)
{
    QSqlQuery query("DELETE FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ?");
    query.addBindValue(tournamentCategoryUID);
    query.exec();
}

QVector<long long> DBUtils::getOrderUIDs(long long UIDtournamentCategory)
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

QVector<long long> DBUtils::getTournamentCategoryUIDs(long long tournamentUID)
{
    QVector<long long> uids;
    QSqlQuery query(
                "SELECT * "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE TOURNAMENT_FK = ? "
                "ORDER BY TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, WEIGHT_FROM, WEIGHT_TILL");
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
                "FROM GRIDS A "
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

QString DBUtils::insertTournamentCaregory(
        long long ageCatUID, int ageFrom, int ageTill, QVector<double> weights,
        long long tournamentUID, long long typeUID, long long sexUID,
        int durationFighting, int durationBreak, int roundCount,
        int IN_CASE_TIE, int DURATION_EXTRA_ROUND,
        QString ageUnit, QString wordAgeFrom, QString wordAgeTill,
        QString weightUnit, QString wordWeightFrom, QString wordWeightTill,
        int pointPanelMode
        )
{
    QString newCategoryMsg = "Добавлены новые категории:\n";
    QString errors = "Ошибки:\n";

    if (IN_CASE_TIE != 2)
        DURATION_EXTRA_ROUND = 0;

    for (int index = 0; index + 1 < weights.size(); index++)
    {
        double weightFrom = weights[index];
        double weightTill = weights[index + 1];


        QString age;
        if      (ageFrom == 0)  age = wordAgeTill + QString::number(ageTill) + " " + ageUnit;
        else if (99 <= ageTill) age = wordAgeFrom + QString::number(ageFrom) + " " + ageUnit;
        else                    age = QString::number(ageFrom) + "-" + QString::number(ageTill) + " " + ageUnit;

        QString weight;
        if      (weightFrom == 0)   weight = wordWeightTill + DBUtils::roundDouble(weightTill, 3) + " " + weightUnit;
        else if (300 <= weightTill) weight = wordWeightFrom + DBUtils::roundDouble(weightFrom, 3) + " " + weightUnit;
        else                        weight = DBUtils::roundDouble(weightFrom, 3) + "-" + DBUtils::roundDouble(weightTill, 3) + " " + weightUnit;


        QString modifyName =
                DBUtils::getField("NAME", "TYPES", typeUID) + ", " +
                DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + ", " +
                age + ", " +
                weight + ".";

        QSqlQuery query;
        if (!query.prepare("INSERT INTO TOURNAMENT_CATEGORIES( "
                           "NAME, AGE_CATEGORY_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL, "
                           "SEX_FK, TYPE_FK, TOURNAMENT_FK, "
                           "DURATION_FIGHING, DURATION_BREAK, ROUND_COUNT, "
                           "IN_CASE_TIE, DURATION_EXTRA_ROUND, "
                           "AGE, WEIGHT, "
                           "POINT_PANEL_MODE_FK) "
                           "VALUES (?, ?, ?, ?, ?, ?,    ?, ?, ?,   ?, ?, ?,   ?, ?,     ?, ?,  ?)"))
            qDebug() << query.lastError().text();
        query.addBindValue(modifyName);
        query.addBindValue(ageCatUID);
        query.addBindValue(ageFrom);
        query.addBindValue(ageTill);
        query.addBindValue(weightFrom);
        query.addBindValue(weightTill);

        query.addBindValue(sexUID);
        query.addBindValue(typeUID);
        query.addBindValue(tournamentUID);

        query.addBindValue(durationFighting);
        query.addBindValue(durationBreak);
        query.addBindValue(roundCount);

        query.addBindValue(IN_CASE_TIE);
        query.addBindValue(DURATION_EXTRA_ROUND);

        query.addBindValue(age);
        query.addBindValue(weight);

        query.addBindValue(pointPanelMode);

        if (!query.exec())
        {
            qDebug() << tournamentUID << typeUID << sexUID << ageFrom << ageTill
                     << weightFrom << weightTill << query.lastError().text();
            errors += modifyName + "\n" +
                      query.lastError().databaseText() + "\n" +
                      query.lastError().driverText() + "\n\n";
        }
        else
        {
            newCategoryMsg += "\t" + modifyName + "\n";
        }

        query.clear();
    }

    return newCategoryMsg + "\n\n" + errors;
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

int DBUtils::getMaxCountOfRings(const int tournamentUID, const int day)
{
    QSqlQuery query;
    if (!query.prepare("SELECT MAX(RING) AS MAXRING "
                       "FROM SCHEDULES "
                       "WHERE "
                       "    TOURNAMENT_FK = ? AND "
                       "    DAY = ? "))
    {
        qDebug() << query.lastError();
    }
    query.addBindValue(tournamentUID);
    query.addBindValue(day);

    query.exec();
    if (query.lastError().isValid())
        qDebug() << query.lastError();

    int maxCountOfRing = 1;
    if (query.next())
    {
        maxCountOfRing = query.value("MAXRING").toInt() + 1;
    }
    return maxCountOfRing;
}

QSqlQuery*DBUtils::getSchelder(const int tournamentUID, const int day, const int ring)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "SELECT * "
            "FROM "
            "   SCHEDULES "
            "WHERE "
            "   TOURNAMENT_FK = ? AND "
            "   DAY = ? AND "
            "   RING = ? "
            "ORDER "
            "   BY ORDER_NUMBER"
            ))
    {
        qDebug() << q->lastError();
    }
    q->addBindValue(tournamentUID);
    q->addBindValue(day);
    q->addBindValue(ring);
    if (q->lastError().isValid())
        qDebug() << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << q->lastError();

    return q;
}

bool DBUtils::updateOrderNumberOfRecordOfSchedule(
        const int tournamentUID,
        const int day,
        const int ring,
        const int order,
        const int newOrder)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "UPDATE "
            "SCHEDULES "
            "SET "
            "   ORDER_NUMBER = ? "
            "WHERE "
            "   TOURNAMENT_FK = ? AND "
            "   DAY = ? AND "
            "   RING = ? AND "
            "   ORDER_NUMBER = ? "
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(newOrder);

    q->addBindValue(tournamentUID);
    q->addBindValue(day);
    q->addBindValue(ring);
    q->addBindValue(order);

    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    int res = q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    delete q;
    return res;
}

bool DBUtils::insertInSchedule(const int tournamentUID, const int day, const int ring, const int order, const int uidTC, const int level, const QString name)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "INSERT INTO SCHEDULES ( "
            "   TOURNAMENT_FK, "
            "   DAY, "
            "   RING, "
            "   ORDER_NUMBER, "
            "   TOURNAMENT_CATEGORY_FK, "
            "   LEVEL, "
            "   NAME "
            ") "
            "VALUES (?,?,?,?,  ?,?,?)"
            ))
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(tournamentUID);
    q->addBindValue(day);
    q->addBindValue(ring);
    q->addBindValue(order);

    q->addBindValue(uidTC);
    q->addBindValue(level);
    q->addBindValue(name);

    if (q->lastError().isValid())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << q->lastError();
    int res = q->exec();
    if (q->lastError().isValid())
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << q->lastError() << q->lastQuery()
                 << tournamentUID
                 << day
                 << ring
                 << order;
    delete q;
    return res;
}

bool DBUtils::deleteInSchedule(const int tournamentUID, const int day, const int ring, const int order)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "DELETE "
            "FROM"
            "   SCHEDULES "
            "WHERE "
            "   TOURNAMENT_FK = ? AND "
            "   DAY = ? AND "
            "   RING = ? AND "
            "   ORDER_NUMBER = ? "
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(tournamentUID);
    q->addBindValue(day);
    q->addBindValue(ring);
    q->addBindValue(order);

    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError() << q->lastQuery()
                 << tournamentUID
                 << day
                 << ring
                 << order;
    return q;
}

QSqlQuery*DBUtils::getDateRingOrderFromSchedule(const int tournamentCategoryUID, const int level)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "SELECT * "
            "FROM SCHEDULES "
            "WHERE "
            "   TOURNAMENT_CATEGORY_FK = ? AND "
            "   LEVEL = ?"
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(tournamentCategoryUID);
    q->addBindValue(level);

    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    return q;
}

int DBUtils::getAnotherRing(const int tournamentCategoryUID, const int day, const int ring)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "SELECT * "
            "FROM SCHEDULES "
            "WHERE "
            "   TOURNAMENT_CATEGORY_FK = ? AND "
            "   DAY = ? AND "
            "   RING != ?"
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(tournamentCategoryUID);
    q->addBindValue(day);
    q->addBindValue(ring);

    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();

    int anotherRing = -1;
    if (q->next())
    {
        anotherRing = q->value("RING").toInt();
    }
    delete q;
    return anotherRing;
}

std::tuple<int, int, int> DBUtils::getDayRingOrder(const int tournamentCategoryUID, const int level)
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "SELECT * "
            "FROM SCHEDULES "
            "WHERE "
            "   TOURNAMENT_CATEGORY_FK = ? AND "
            "   LEVEL == ?"
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->addBindValue(tournamentCategoryUID);
    q->addBindValue(level);

    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();

    std::tuple<int, int, int> tuple(-1, -1, -1);
    if (q->next())
    {
        tuple = std::make_tuple(
                    q->value("DAY").toInt(),
                    q->value("RING").toInt(),
                    q->value("ORDER_NUMBER").toInt());
    }
    delete q;
    return tuple;
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

QMap<QString, QSqlRecord> DBUtils::get_NAME_RUS__RELATION_TABLE_NAME()
{
    QSqlQuery *q = new QSqlQuery;
    if (!q->prepare(
            "SELECT * "
            "FROM FIELD_TRANSLATES "
            ))
    {
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();
    }
    q->exec();
    if (q->lastError().isValid())
        qDebug() << __PRETTY_FUNCTION__ << q->lastError();

    QMap<QString, QSqlRecord> map;
    while (q->next())
    {
        map[q->value("NAME_ENG").toString()] = q->record();
    }
    delete q;
    return map;
}
