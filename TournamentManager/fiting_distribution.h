#ifndef FITINGDISTRIBUTION_H
#define FITINGDISTRIBUTION_H

#include <QObject>
#include <QSqlDatabase>

class FitingDistribution : public QObject
{
    Q_OBJECT

public:
    explicit FitingDistribution(const QSqlDatabase &m_database, long long tournamentUID);

private:

signals:

public slots:
};

#endif // FITINGDISTRIBUTION_H
