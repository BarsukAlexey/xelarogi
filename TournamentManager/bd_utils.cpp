#include "bd_utils.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDate>


QString BDUtils::getNameTournamentByUID(const QSqlDatabase& database, const long long UID)
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

QString BDUtils::getTypeNameByUID(const QSqlDatabase& database, long long UID)
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

QString BDUtils::get_SHORTNAME_FROM_SEXES(const QSqlDatabase& database, long long UID)
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

QStringList BDUtils::get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& database, long long UID)
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

QString BDUtils::get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID)
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

QString BDUtils::get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID)
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

QString BDUtils::get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID)
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
