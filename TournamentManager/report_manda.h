#ifndef REPORTMANDA_H
#define REPORTMANDA_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"

#include <QAxWidget>
#include <QAxObject>
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class ReportManda : public QObject
{
    Q_OBJECT
public:
    explicit ReportManda(const long long TOURNAMENT_FK);

signals:

public slots:
};

#endif // REPORTMANDA_H
