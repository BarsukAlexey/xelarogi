#ifndef GENERATETOURNAMENTCATEGORIESDIALOG_H
#define GENERATETOURNAMENTCATEGORIESDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

#include "sqltablemanager.h"

namespace Ui {
class GenerateTournamentCategoriesDialog;
}


class GenerateTournamentCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent = 0);
    ~GenerateTournamentCategoriesDialog();

    static QString insertInDB(long long ageCatUID, int ageFrom, int ageTill, QVector<double> weights,
                              long long tournamentUID, long long typeFK, long long sexFK,
                              int durationFighting, int durationBreak, int roundCount,
                              int IN_CASE_TIE, int DURATION_EXTRA_ROUND,
                              QString ageUnit, QString wordAgeFrom, QString wordAgeTill,
                              QString weightUnit, QString wordWeightFrom, QString wordWeightTill);
private slots:
    void on_pushButton_clicked();
    void on_pushButtonAddAgeCategory_clicked();
    void fillComboBoxAgeCategory();

private:
    void fillSexCB();
    void fillTypeCB();
    void fillTie();


private:
    Ui::GenerateTournamentCategoriesDialog *ui;
    long long mTournamentUID;
};

#endif // GENERATETOURNAMENTCATEGORIESDIALOG_H
