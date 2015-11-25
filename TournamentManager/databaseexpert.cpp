#include "databaseexpert.h"

QMap<QString, QString> DataBaseExpert::fieldTranslationMap(const QSqlDatabase& database)
{
    QMap<QString, QString> result;

    QSqlQuery query("select NAME_ENG, NAME_RUS from FIELD_TRANSLATES");
    if (!query.exec())
        qDebug() << database.lastError().text();
    else
    {
        while (query.next())
        {
            result[query.value("NAME_ENG").toString()] = query.value("NAME_RUS").toString();
        }
    }

    return result;
}

QString DataBaseExpert::getTableNameByField(const QString &field)
{
    QString tableName = field;
    if (field.size() > 3 && field.right(3) == "_FK")
    {
        tableName = field.left(field.size() - 3);
        if (tableName == "COUNTRY")
            tableName = "COUNTRIES";
        else if (tableName == "SEX")
            tableName = "SEXES";
        else if (tableName == "SPORT_CATEGORY")
            tableName = "SPORT_CATEGORIES";
        else if (tableName == "TOURNAMENT_CATEGORY")
            tableName = "TOURNAMENT_CATEGORIES";
        else
            tableName = tableName + "S";
    }

    return tableName;
}

DataBaseExpert &DataBaseExpert::instance()
{
    static DataBaseExpert inst;
    return inst;
}
