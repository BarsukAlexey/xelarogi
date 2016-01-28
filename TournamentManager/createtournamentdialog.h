#ifndef CREATETOURNAMENTDIALOG_H
#define CREATETOURNAMENTDIALOG_H

#include <QDialog>

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
    Ui::CreateTournamentDialog *ui;
};

#endif // CREATETOURNAMENTDIALOG_H
