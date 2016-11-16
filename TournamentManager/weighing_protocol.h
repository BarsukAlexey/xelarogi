#ifndef WEIGHINGPROTOCOL_H
#define WEIGHINGPROTOCOL_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"

#include <QApplication>
#include <QAxObject>
#include <QAxWidget>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QProgressDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

class WeighingProtocol : public QObject
{
    Q_OBJECT
public:
    explicit WeighingProtocol(const long long tournamentUID, QObject *parent = 0);

signals:

public slots:
};

#endif // WEIGHINGPROTOCOL_H
