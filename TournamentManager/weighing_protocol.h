#ifndef WEIGHINGPROTOCOL_H
#define WEIGHINGPROTOCOL_H

#include <QObject>
#include <QSqlDatabase>

class WeighingProtocol : public QObject
{
    Q_OBJECT
public:
    explicit WeighingProtocol(const QSqlDatabase &database, const long long tournamentUID, QObject *parent = 0);

signals:

public slots:
};

#endif // WEIGHINGPROTOCOL_H
