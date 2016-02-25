#ifndef WINNERREPORT_H
#define WINNERREPORT_H

#include <QObject>
#include <QSqlDatabase>

class WinnerReport : public QObject
{
    Q_OBJECT
public:
    explicit WinnerReport(const QSqlDatabase& database, const long long tournamentUID, QObject* parent);

signals:

public slots:
};

#endif // WINNERREPORT_H
