#ifndef TOURNAMENTGRIDDIALOG_H
#define TOURNAMENTGRIDDIALOG_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "tournamentmanager.h"

namespace Ui {
class TournamentGridDialog;
}

class TournamentGridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentGridDialog(const QSqlDatabase& database, QWidget *parent = 0);
    ~TournamentGridDialog();

private slots:
    void generate();

private:
    Ui::TournamentGridDialog *ui;
};

#endif // TOURNAMENTGRIDDIALOG_H
