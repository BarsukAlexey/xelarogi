#include "ebnutvbazu.h"
#include "db_utils.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>


void EbnutVBazu::f(const QSqlDatabase &database, long long tournamentUID)
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



void EbnutVBazu::setRandomWinner(const QSqlDatabase& database, long long tournamentUID)
{
    QSqlQuery query("SELECT DISTINCT TOURNAMENT_CATEGORIES_FK FROM GRID");
    if (!query.exec())
    {
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
        return ;
    }
    while (query.next())
    {
        qlonglong TOURNAMENT_CATEGORIES_FK = query.value("TOURNAMENT_CATEGORIES_FK").toLongLong();
        qDebug() << "TOURNAMENT_CATEGORIES_FK: " << TOURNAMENT_CATEGORIES_FK;
        QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(TOURNAMENT_CATEGORIES_FK);
        for (int i = nodes.size() - 1; 0 <= i; --i)
        {
            int v = i + 1;
            int child = rand() % 2? 2 * v + 1 : 2 * v;
            if (child <= nodes.size())
            {
                QSqlQuery q("UPDATE GRID SET ORDER_FK = ?  WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                if (nodes[child - 1].UID == 0)
                {
                    qDebug() << "Fuck";
                    return;
                }
                q.bindValue(0, nodes[v - 1].UID = nodes[child - 1].UID);
                q.bindValue(1, TOURNAMENT_CATEGORIES_FK);
                q.bindValue(2, v);
                if (!q.exec())
                {
                    qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << q.lastError().text() << "\n" << q.lastQuery() << "\n";
                    return ;
                }
            }
        }
    }
    qDebug() << "DONE setRandomWinner";
}
