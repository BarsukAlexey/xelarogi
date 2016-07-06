#ifndef WINNERREPORT_H
#define WINNERREPORT_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"


#include <QAxObject>
#include <QAxWidget>
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class WinnerReport : public QObject
{
    Q_OBJECT
public:
    explicit WinnerReport(const long long tournamentUID, QObject* parent = 0);

signals:

public slots:
};

#endif // WINNERREPORT_H
