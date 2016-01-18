#ifndef TOURNAMENTADMINDIALOG_H
#define TOURNAMENTADMINDIALOG_H

#include <QDialog>

namespace Ui {
class TournamentAdminDialog;
}

class TournamentAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TournamentAdminDialog(QWidget *parent = 0);
    ~TournamentAdminDialog();

private:
    Ui::TournamentAdminDialog *ui;
};

#endif // TOURNAMENTADMINDIALOG_H
