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

class ReportManda
{
public:
    static void report(const long long tournamentUID);

};

#endif // REPORTMANDA_H
