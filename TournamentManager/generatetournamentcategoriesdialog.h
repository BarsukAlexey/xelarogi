#ifndef GENERATETOURNAMENTCATEGORIESDIALOG_H
#define GENERATETOURNAMENTCATEGORIESDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

namespace Ui {
class GenerateTournamentCategoriesDialog;
}

class GenerateTournamentCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent = 0);
    ~GenerateTournamentCategoriesDialog();

private:
    void fillSexCB();
    void fillTypeCB();

private:
    Ui::GenerateTournamentCategoriesDialog *ui;
    long long mTournamentUID;
};

#endif // GENERATETOURNAMENTCATEGORIESDIALOG_H
