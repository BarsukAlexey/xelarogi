#ifndef CHOOSETOURNAMENTDIALOG_H
#define CHOOSETOURNAMENTDIALOG_H

#include <QDialog>

#include "tournamentadmindialog.h"

namespace Ui {
class ChooseTournamentDialog;
}

class ChooseTournamentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseTournamentDialog(QWidget *parent = 0);
    ~ChooseTournamentDialog();

private:
    Ui::ChooseTournamentDialog *ui;
};

#endif // CHOOSETOURNAMENTDIALOG_H
