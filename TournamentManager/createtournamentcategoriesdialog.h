#ifndef CREATETOURNAMENTCATEGORIESDIALOG_H
#define CREATETOURNAMENTCATEGORIESDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QMenu>
#include <QAction>
#include <QDialogButtonBox>
#include <QSqlRecord>
#include <QSortFilterProxyModel>

#include "generatetournamentcategoriesdialog.h"
#include "db_utils.h"
#include "createtypedialog.h"

namespace Ui {
class CreateTournamentCategoriesDialog;
}

class CreateTournamentCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent = 0);
    ~CreateTournamentCategoriesDialog();

private slots:
    void on_pushButtonAddGroupOfCaterories_clicked();

private:

private:
    Ui::CreateTournamentCategoriesDialog *ui;
    long long mTournamentUID;
};

#endif // CREATETOURNAMENTCATEGORIESDIALOG_H
