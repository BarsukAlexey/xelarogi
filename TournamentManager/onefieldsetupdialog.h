#ifndef ONEFIELDSETUPDIALOG_H
#define ONEFIELDSETUPDIALOG_H

#include <QDebug>

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class OneFieldSetupDialog;
}

class OneFieldSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneFieldSetupDialog(long long tournamentUID, QString fieldName, QWidget *parent = 0);
    ~OneFieldSetupDialog();

private:
    void updateListWidgets();

private:
    Ui::OneFieldSetupDialog *ui;
    long long mTournamentUID;
    QString mFieldName;
};

#endif // ONEFIELDSETUPDIALOG_H
