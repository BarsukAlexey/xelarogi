#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QDebug>
#include <algorithm>
#include <QAxWidget>
#include <QAxObject>

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

#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>

#include <algorithm>
#include <QThread>
#include "forma_dvertisement.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    const QString nameSaveFile = "save.json";
    QVector<QVector<QImage>> flags;
    QVector<int> extraRound;
    QTimer *advTimer;


    QVector<QString> images;
    int posImage = 0;
    QVector<FormAdvertisement*> formsForAdvertisement;
    bool showAdvertisement = true;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QJsonDocument loadJSON();
    void update();

private slots:
    void updateAdvertisement();

};

#endif // MAINWINDOW_H
