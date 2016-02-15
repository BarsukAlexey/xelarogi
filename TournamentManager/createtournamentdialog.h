#ifndef CREATETOURNAMENTDIALOG_H
#define CREATETOURNAMENTDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class CreateTournamentDialog;
}

class CreateTournamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentDialog(QWidget *parent = 0);
    ~CreateTournamentDialog();

private:
    bool tournamentExist(QString name, QDate beginDate, QDate endDate);

private:
    Ui::CreateTournamentDialog *ui;
};

#endif // CREATETOURNAMENTDIALOG_H
