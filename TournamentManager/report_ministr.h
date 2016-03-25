#ifndef REPORMINISTR_H
#define REPORMINISTR_H

#include <QObject>
#include <QSqlDatabase>
#include <QAxObject>

class ReporMinistr : public QObject
{
    Q_OBJECT
public:
    explicit ReporMinistr(const long long tournamentUID);

private:
    static void f2(QAxObject *sheet, const long long tournamentUID);
    static void f3(QAxObject *sheet, const long long tournamentUID);
signals:

public slots:
};

#endif // REPORMINISTR_H
