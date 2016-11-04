#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countryiconsdialog.h"
#include "createtournamentcategoriesdialog.h"
#include "createtournamentdialog.h"
#include "createtournamentordersdialog.h"
#include "dialogschedule.h"
#include "dialogschedule2.h"
#include "dialogtournamentgrid.h"
#include "ebnutvbazu.h"
#include "fighting_pairs.h"
#include "fiting_distribution.h"
#include "formdipl.h"
#include "generatetournamentcategoriesdialog.h"
#include "handbookdialog.h"
#include "logindialog.h"
#include "report_manda.h"
#include "report_ministr.h"
#include "trophygenerator.h"
#include "trophygeneratorsettingsdialog.h"
#include "weighing_protocol.h"
#include "winner_report.h"

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
    void on_pushButtonGrid_clicked();
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
};

#endif // MAINWINDOW_H
