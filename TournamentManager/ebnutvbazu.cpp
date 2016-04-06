#include "ebnutvbazu.h"
#include "db_utils.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>
#include <utility>
#include <generatetournamentcategoriesdialog.h>


void EbnutVBazu::f(const QSqlDatabase &database, long long )
{
    qDebug() << "ebnutVBazyGovno";
    QSqlQuery *query;


    query = new QSqlQuery("DELETE FROM ORDERS", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    query = new QSqlQuery("DELETE FROM TOURNAMENT_CATEGORIES", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    query = new QSqlQuery("DELETE FROM GRID", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    long long UID_TOURNAMENT_CATEGORIES = 10;
    long long UID_people = 1000;
    int count_people = -1;
    const char* types[5] = {"light contact", "low kick", "full contact"};

    for(int age = 10, stepAge = 10; age <= 30; age += stepAge)
    {
        for(int weight = 30, stepWeight = 30; weight <= 100; weight += stepWeight)
        {
            for (int sex = 1; sex <= 2; ++sex)
            {
                for (int type = 1; type <= 3; ++type)
                {
                    ++UID_TOURNAMENT_CATEGORIES;
                    //count_people = (count_people + 1) % 17;
                    ++count_people;

                    query = new QSqlQuery("INSERT INTO TOURNAMENT_CATEGORIES VALUES (?, ?, ?, ?, ?, ?, 1, ?, ?,   ?, ?, ?)", database);
                    QString str;

                    str.sprintf("%s от %d до %d лет, от %d до %d кг, %s", (sex==1? "М" : "Ж"), age, age + stepAge, weight, weight + stepWeight, types[type - 1]);
                    query->bindValue(0, UID_TOURNAMENT_CATEGORIES);
                    query->bindValue(1, str);
                    query->bindValue(2, age);
                    query->bindValue(3, age + stepAge);
                    query->bindValue(4, weight);
                    query->bindValue(5, weight + stepWeight);
                    query->bindValue(6, type);
                    query->bindValue(7, sex);
                    query->bindValue(8, 30);
                    query->bindValue(9, 20);
                    query->bindValue(10, 3);
                    if (!query->exec())
                    {
                        qDebug() << __PRETTY_FUNCTION__ << __LINE__ << " " << query->lastError().text() << " " << query->lastQuery();
                    }
                    delete query;


                    for (int j = 0; j < count_people; ++j, ++UID_people){
                        query = new QSqlQuery("INSERT INTO ORDERS VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", database);
                        query->bindValue(0, UID_people);
                        query->bindValue(1, "Name" + QString('A' + j));
                        query->bindValue(2, "Second" + QString(char('A' + j)));
                        query->bindValue(3, "Patr" + QString(char('A' + j)));
                        QDate date;
                        date.addYears(- age - stepAge / 2);
                        query->bindValue(4, date);
                        query->bindValue(5, sex);
                        query->bindValue(6, weight + stepWeight / 2);
                        query->bindValue(7, type);
                        query->bindValue(8, UID_TOURNAMENT_CATEGORIES);
                        query->bindValue(9, "1");
                        query->bindValue(10, "1");
                        query->bindValue(11, "2");
                        query->bindValue(12, "1");
                        query->bindValue(13, "1");
                        query->bindValue(14, "1");

                        query->bindValue(15, "true");
                        query->bindValue(16, "true");
                        query->bindValue(17, "true");
                        query->bindValue(18, "true");
                        if (!query->exec())
                            qDebug() << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
                        delete query;
                    }
                    /**/
                    qDebug() << "DONE count_people: " << count_people;
                }
            }
        }
    }
}



void EbnutVBazu::setRandomWinner()
{
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES ORDER BY UID");
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__  << query.lastError().text() << query.lastQuery();
        return ;
    }
    while (query.next())
    {
        qlonglong tcUID = query.value("UID").toLongLong();
        qDebug() << "TOURNAMENT_CATEGORIES_FK: " << tcUID;
        QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(tcUID);
        if (tcUID==1225)
        {
            tcUID = tcUID;
        }
        for (int i = nodes.size() - 1; 0 <= i; --i)
        {
            int v = i + 1;
            int child = rand() % 2? 2 * v + 1 : 2 * v;
            if (child <= nodes.size())
            {
                QSqlQuery q("UPDATE GRID SET ORDER_FK = ?, result = ?  WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                if (nodes[child - 1].UID == 0)
                {
                    qDebug() << "Fuck";
                    return;
                }
                q.addBindValue(nodes[v - 1].UID = nodes[child - 1].UID);
                int r = rand() % 3; q.addBindValue(QString::number(r) + ":" + QString::number(3 - r));
                q.addBindValue(tcUID);
                q.addBindValue(v);
                if (!q.exec())
                {
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__  << q.lastError().text() << q.lastQuery();
                    return ;
                }
            }
        }
    }
    qDebug() << "DONE setRandomWinner";
}

void EbnutVBazu::setTournamentCat(long long tournamentUID)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;

    for(QString s : {
        "DELETE FROM AGE_CATEGORIES; ",
        "DELETE FROM CLUBS; ",
        "DELETE FROM COACHS; ",
        "DELETE FROM COUNTRIES; ",
        "DELETE FROM GRID; ",
        "DELETE FROM ORDERS; ",
        "DELETE FROM REGION_UNITS; ",
        "DELETE FROM REGIONS; ",
        "DELETE FROM SPORT_CATEGORIES; ",
        "DELETE FROM TOURNAMENT_CATEGORIES; ",
        "DELETE FROM SPORT_CATEGORIES; ",
        "DELETE FROM TYPES; "})
    {
        query.clear();
        if(!query.prepare(s))
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        if(!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }

    QVector<std::pair<int, QString>> types;
    types
            << std::make_pair(100, "Лоу-кик")
            << std::make_pair(101, "Фулл-контакт")
            << std::make_pair(102, "Лайт-контакт")
            << std::make_pair(103, "Поинтфайтинг");

    for(std::pair<int, QString> type : types)
    {
        query.clear();
        if(!query.prepare("INSERT INTO TYPES VALUES (?,?)"))
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        query.addBindValue(type.first);
        query.addBindValue(type.second);
        if(!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }



    for (std::tuple<int, QString, int, int, int> tup : {
         std::make_tuple(10, QString("Мл. кадеты"), 1, 0, 7),

         std::make_tuple(11, QString("Кадеты"), 1, 8, 9),
         std::make_tuple(12, QString("Девочки"), 2, 8, 9),

         std::make_tuple(13, QString("Мл. юноши"), 1, 10, 12),
         std::make_tuple(14, QString("Мл. девушки"), 2, 10, 12),

         std::make_tuple(15, QString("Юноши"), 1, 13, 15),
         std::make_tuple(16, QString("Девушки"), 2, 13, 15),

         std::make_tuple(17, QString("Юниоры"), 1, 16, 18),
         std::make_tuple(18, QString("Юниорки"), 2, 16, 18),

         std::make_tuple(19, QString("Мужчины"), 1, 18, 99),
         std::make_tuple(20, QString("Женщины"), 2, 18, 99),})
    {
        query.clear();
        if(!query.prepare("INSERT INTO AGE_CATEGORIES VALUES (?,?,?)"))
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        query.addBindValue(std::get<0>(tup));
        query.addBindValue(std::get<1>(tup));
        query.addBindValue(std::get<2>(tup));
        if(!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }

        for(std::pair<int, QString> type : types)
        {
            QVector<double> weigths;
            QVector<int> time;
            weigths << 0;
            if      (std::get<0>(tup) <= 10) weigths << 20 << 22 << 25 << 28 << 32 << 37;
            else if (std::get<0>(tup) <= 12) weigths << 20 << 22 << 25 << 28 << 32 << 37 << 42;
            else if (std::get<0>(tup) <= 14) weigths << 28 << 32 << 37 << 42 << 47;
            else if (std::get<0>(tup) <= 16) weigths << 42 << 46 << 50 << 55 << 60 << 65;
            else if (std::get<0>(tup) <= 18) weigths << 50 << 55 << 60 << 65 << 70;
            else if (std::get<0>(tup) <= 20) weigths << 50 << 55 << 60 << 65 << 70;
            weigths << 10000;

            if      (std::get<0>(tup) <= 12) time << 60  << 30 << 2;
            else if (std::get<0>(tup) <= 14) time << 90  << 45 << 2;
            else if (std::get<0>(tup) <= 20) time << 120 << 60 << 2;

            GenerateTournamentCategoriesDialog::insertInDB(
                        std::get<0>(tup),
                        std::get<3>(tup), std::get<4>(tup),
                        weigths, tournamentUID, type.first, std::get<2>(tup),
                        time[0], time[1], time[2]
                );
        }
    }

    QSqlDatabase::database().commit();
}
