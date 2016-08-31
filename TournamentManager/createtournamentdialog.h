#ifndef CREATETOURNAMENTDIALOG_H
#define CREATETOURNAMENTDIALOG_H

#include <QCloseEvent>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class CreateTournamentDialog;
}

class CreateTournamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentDialog(QWidget *parent = 0);
    ~CreateTournamentDialog();


     //void closeEvent(QCloseEvent *event);

private:
    Ui::CreateTournamentDialog *ui;

public slots:
    void checkValues(QAbstractButton *);
};

#endif // CREATETOURNAMENTDIALOG_H
