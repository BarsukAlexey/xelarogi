#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>
#include <algorithm>
#include <iostream>

#include <QMainWindow>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QTreeWidgetItem>

#include "tournamentmanager.h"
//#include "tournamentgriddialog.h"
#include "createtournamentdialog.h"
#include "createtournamentordersdialog.h"
#include "createtournamentcategoriesdialog.h"
#include "generatetournamentcategoriesdialog.h"
#include "logindialog.h"
#include "trophygeneratorsettingsdialog.h"
#include "trophygenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent * event) override;

private slots:
    void on_pushButtonGrid_clicked();
    void on_pushButtonFightinDistribution_clicked();
    void on_pushButtonPair_clicked();
    void on_pushButtonProtokolVzveshinanya_clicked();
    void on_pushButtonWinnerReport_clicked();
    void on_pushButtonLoadWinner_clicked();
    void on_manda_clicked();
    void on_btn_report_ministr_clicked();


private:
    void updateTournamentTreeWidget();
    void connectButtons();
    

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_database;
};

#endif // MAINWINDOW_H
