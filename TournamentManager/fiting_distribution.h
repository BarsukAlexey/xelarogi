#ifndef FITINGDISTRIBUTION_H
#define FITINGDISTRIBUTION_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"
#include "renderareawidget.h"

#include <QApplication>
#include <QAxObject>
#include <QAxWidget>
#include <QDate>
#include <QDebug>
#include <QDialog>
#include <QObject>
#include <QProgressDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
