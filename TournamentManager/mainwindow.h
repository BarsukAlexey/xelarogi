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

#include "tournamentmanager.h"

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
    void on_btnExcel_clicked();
    void on_pushButton_clicked();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase m_database;
};

#endif // MAINWINDOW_H
