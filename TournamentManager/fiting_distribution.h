#ifndef FITINGDISTRIBUTION_H
#define FITINGDISTRIBUTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QAxObject>

class FitingDistribution : public QObject
{
    Q_OBJECT

public:
    explicit FitingDistribution(const QSqlDatabase &m_database, long long tournamentUID);

private:
    void initTableHeads(QAxObject *sheet, int& rowCount, const QStringList& days);


signals:

public slots:
};

#endif // FITINGDISTRIBUTION_H
