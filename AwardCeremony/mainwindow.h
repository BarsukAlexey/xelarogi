#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QKeyEvent>
#include <QShortcut>
#include <QMediaPlayer>
#include <QBuffer>
#include <QCloseEvent>
#include <QFileSystemModel>
#include <QDirIterator>

#include "dialogawardpanel.h"
#include "qitemdelegateformusiclist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DialogAwardWidget* awardPanel, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoadData_triggered();
    void onSelectionChanged();
    void onPressSpace();

    void on_pushButtonAll_clicked();
    void on_pushButtonI_clicked();
    void on_pushButtonII_clicked();
    void on_pushButtonIII_clicked();
    void on_pushButtonIV_clicked();

    void onMusicSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onGiveMeNextMusic();

private:
    void showPlayer(int player);
    bool dfs(QModelIndex index);
    void loadData(const QString& openFileName);

protected:
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;

    QVector<QString> TCs;
    QVector<QVector<QString>> players;

    QVector<QVector<int>> names;
    QVector<QVector<int>> flags;
    QVector<QVector<int>> hymns;

    QMap<int, QString> mapNames;
    QMap<int, QByteArray> mapFlag;
    QMap<int, QByteArray> mapHymn;

    DialogAwardWidget* awardPanel;

    int currentRow;
    QVector<bool> shown;

    QFileSystemModel* model;

};

#endif // MAINWINDOW_H
