#ifndef REPORTMANDA_H
#define REPORTMANDA_H

#include <QObject>
#include <QSqlDatabase>

class ReportManda : public QObject
{
    Q_OBJECT
public:
    explicit ReportManda(const QSqlDatabase& database, const long long TOURNAMENT_FK);

signals:

public slots:
};

#endif // REPORTMANDA_H
