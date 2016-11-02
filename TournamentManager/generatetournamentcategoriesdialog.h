#ifndef GENERATETOURNAMENTCATEGORIESDIALOG_H
#define GENERATETOURNAMENTCATEGORIESDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QStringList>

#include "createtypedialog.h"
#include "db_utils.h"
#include "dialog_create_age_category.h"
#include "dialogsqltablemanager.h"

namespace Ui {
class GenerateTournamentCategoriesDialog;
}


class GenerateTournamentCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent = 0);
    ~GenerateTournamentCategoriesDialog();

private slots:
    void on_accepted();
    void onPushButtonTypeClicked();
    void onPushButtonAddAgeCategoryClicked();

private:
    Ui::GenerateTournamentCategoriesDialog *ui;
    long long mTournamentUID;
    QSqlRelationalTableModel *modelType;
    QSqlRelationalTableModel *modelSex;
    QSqlRelationalTableModel *modelAgeType;
    QSqlRelationalTableModel *modelTie;
};

#endif // GENERATETOURNAMENTCATEGORIESDIALOG_H
