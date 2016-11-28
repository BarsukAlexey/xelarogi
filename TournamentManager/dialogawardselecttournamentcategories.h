#ifndef DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H
#define DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H

#include <QDialog>
#include <QTableWidget>
#include "db_utils.h"
#include "dialogtournamentgrid.h"



namespace Ui {
class DialogAwardSelectTournamentCategories;
}

class DialogAwardSelectTournamentCategories : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAwardSelectTournamentCategories(const int tournamentUID, QWidget *parent = 0);
    ~DialogAwardSelectTournamentCategories();



private slots:
    void on_pushButtonShowGridLeft_clicked();
    void on_pushButtonShowGridRight_clicked();

private:
    static void addRow(QTableWidget* table, const int uidTC);
    void showGrid(QTableWidget* table);
    void updateAllData();

private:
    Ui::DialogAwardSelectTournamentCategories *ui;
    const int tournamentUID;
};

#endif // DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H
