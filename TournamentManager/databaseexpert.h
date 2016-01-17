#ifndef DATABASEEXPERT_H
#define DATABASEEXPERT_H

#include <QObject>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QDebug>

class DataBaseExpert : public QObject
{
    Q_OBJECT
public:
    static QMap<QString, QString> fieldTranslationMap(const QSqlDatabase& database);
    static QMap<QString, QString> ralationTablesForFields(const QSqlDatabase& database);
    static QString getTableNameByField(const QString & field);

private:
    DataBaseExpert() = default;
    DataBaseExpert(const DataBaseExpert&) = delete;
    DataBaseExpert& operator = (const DataBaseExpert&) = delete;

private:
    static DataBaseExpert & instance();
};

#endif // DATABASEEXPERT_H
