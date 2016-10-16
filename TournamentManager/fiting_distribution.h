#ifndef FITINGDISTRIBUTION_H
#define FITINGDISTRIBUTION_H

#include <QObject>
#include <QDialog>
#include <QSqlDatabase>
#include <QAxObject>
#include <QSqlRecord>

class FitingDistribution : public QObject
{
    Q_OBJECT

private:
    QMap<QString, QString> translate;

public:
    explicit FitingDistribution(long long tournamentUID, QObject* parent);

private:
    void initTableHeads(QAxObject *sheet, int& rowCount, const QStringList& days);

signals:

public slots:
};

#endif // FITINGDISTRIBUTION_H
