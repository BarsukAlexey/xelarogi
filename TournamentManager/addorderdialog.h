#ifndef ADDORDERDIALOG_H
#define ADDORDERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class AddOrderDialog;
}

class AddOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrderDialog(long long tournamentUID, QWidget *parent = 0);
    ~AddOrderDialog();

private slots:
    void onOkBtn();

private:
    Ui::AddOrderDialog *ui;

private:
    long long mTournamentUID;
};

#endif // ADDORDERDIALOG_H
