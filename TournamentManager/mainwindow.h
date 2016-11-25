#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "createtournamentcategoriesdialog.h"
#include "createtournamentordersdialog.h"
#include "dialogschedule.h"
#include "dialogschedule2.h"
#include "dialogtournamentgrid.h"
#include "fighting_pairs.h"
#include "fiting_distribution.h"
#include "formdipl.h"
#include "generatetournamentcategoriesdialog.h"
#include "dialogtournamentgrid.h"
#include "fighting_pairs.h"

#include "logindialog.h"
#include "report_manda.h"
#include "report_ministr.h"

#include "weighing_protocol.h"
#include "winner_report.h"
#include "dialogschedule.h"

#include "dialogschedule2.h"
#include "report_manda.h"
#include "report_ministr.h"
#include "dialogaward.h"


#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include <QAxBase>
#include <QAxObject>
#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTreeWidgetItem>
#include <QVariantMap>



class TournamentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TournamentModel(QObject* parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int getUID(int row);
    void selectAndSortData();
private:
    QSqlRelationalTableModel *modelTournament;
};




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonLoadWinner_clicked();
    void on_pushButtonWinnerReport_clicked();
    void on_manda_clicked();
    void on_btn_report_ministr_clicked();

    void on_pushButtonAward_clicked();

private:
    void onAction(QString table);
    void onButton(const QString &field, const QString& table);

    Ui::MainWindow *ui;
    TournamentModel* model;
    int tournamentUID;

};

#endif // MAINWINDOW_H
