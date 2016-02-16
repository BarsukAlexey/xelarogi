#ifndef TOURNAMENTADMINDIALOG_H
#define TOURNAMENTADMINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "onefieldsetupdialog.h"
#include "createtournamentordersdialog.h"

namespace Ui {
class TournamentAdminDialog;
}

class TournamentAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentAdminDialog(const QSqlDatabase& database, long long tournamentUID, QWidget *parent = 0);
    ~TournamentAdminDialog();

private slots:
    void on_createOrdersBtn_clicked();

private:
    Ui::TournamentAdminDialog *ui;
};

#endif // TOURNAMENTADMINDIALOG_H
