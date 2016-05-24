#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
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
#include <QTimer>
#include "forma_dvertisement.h"

#include "fightingtable2.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    const QString nameSaveFile = ("save.json");
    const QString nameSettingFile = ("setting.json");

    Ui::MainWindow *ui;
    QVector<QVector<QImage>> flags;
    QTimer advTimer;

    QVector<QString> images;
    int posImage = 0;
    QVector<FormAdvertisement*> formsForAdvertisement;
    bool showAdvertisement;
    bool classicSkin;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QJsonDocument loadJSON(const QString& path);

private:
    void update();

private slots:
    void updateAdvertisement();

};

#endif // MAINWINDOW_H
