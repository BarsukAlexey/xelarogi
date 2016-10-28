#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QPainter>
#include <QPaintEvent>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <vector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QVariantMap>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>



#include "createtournamentdialog.h"
#include "createtournamentordersdialog.h"
#include "createtournamentcategoriesdialog.h"
#include "generatetournamentcategoriesdialog.h"
#include "logindialog.h"
#include "trophygeneratorsettingsdialog.h"
#include "trophygenerator.h"
#include "dialogschedule.h"
#include "report_manda.h"
#include "formdipl.h"
#include "handbookdialog.h"
#include "dialogtournamentgrid.h"
#include "fiting_distribution.h"
#include "fighting_pairs.h"
#include "weighing_protocol.h"
#include "winner_report.h"
#include "ebnutvbazu.h"
#include "report_ministr.h"
#include "countryiconsdialog.h"
#include "dialogschedule2.h"


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
    void on_pushButtonPair_clicked();
    void on_pushButtonProtokolVzveshinanya_clicked();
    void on_pushButtonWinnerReport_clicked();
    void on_pushButtonLoadWinner_clicked();
    void on_manda_clicked();
    void on_btn_report_ministr_clicked();
    void on_pushButtonAddContest_clicked();

private:
    void updateTournamentTreeWidget();
    void connectButtons();
    

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_database;
};

#endif // MAINWINDOW_H
