#ifndef TOURNAMENTGRIDDIALOG2_H
#define TOURNAMENTGRIDDIALOG2_H


#include <QDialog>
#include <QSqlDatabase>

class TournamentGridDialog2 : public QDialog
{
    Q_OBJECT
private:
    const QSqlDatabase& database;
    long long tournamentUID;

public:
    TournamentGridDialog2(const QSqlDatabase &database, long long tournamentUID, QWidget *parent = 0);
    ~TournamentGridDialog2();

private slots:
    void playerChanged();

};

#endif // TOURNAMENTGRIDDIALOG2_H
