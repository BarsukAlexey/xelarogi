#include "bd_utils.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>


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
