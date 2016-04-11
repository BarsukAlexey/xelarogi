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


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QJsonDocument loadJSON();
    void update();

};

#endif // MAINWINDOW_H
