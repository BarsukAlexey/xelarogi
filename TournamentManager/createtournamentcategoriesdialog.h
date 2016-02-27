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
    void onAddBtn();
    void onChangeBtn(long long categoryUID);

private:
    void updateTable();
    void updateDataWidget(long long categoryUID);
    void fillSexComboBox();
    void fillTypeComboBox();
    void selectSexByUID(long long sexUID);
    void selectTypeByUID(long long typeUID);
    void addContextMenu();

private:
    Ui::CreateTournamentCategoriesDialog *ui;
    long long mTournamentUID;
};

#endif // CREATETOURNAMENTCATEGORIESDIALOG_H
