#ifndef FIGHTING_TABLE_H
#define FIGHTING_TABLE_H

#include "formscore.h"
#include "fighting.h"
#include "dialogdisq.h"
#include "formscore.h"

#include <chrono>
#include <ctime>
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
#include <QApplication>
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QDialog>
#include <QMessageBox>
#include <QSound>
#include <QString>
#include <QtGui>
#include <QTimer>
#include <QWidget>
using namespace std::chrono;

namespace Ui {
class FightingTable;
}

class FightingTable : public QDialog
{
    Q_OBJECT

private:
    Fighting *f;

    Ui::FightingTable *ui;
    FormScore *left;
    FormScore *right;
    QRightClickButton *pushButtonStart;
    QRightClickButton *pushButtonDoctor;
    QRightClickButton *pushButtonStop;
    QRightClickButton *cancelLastPenalty;

    const QString nameLeft;
    const QString nameRight;
    const QImage mLeftFlag;
    const QImage mRightFlag;

    const bool isForJudge;
    const bool showAdvertisement;

    QString forceResult;



public:

    FightingTable(Fighting *f,
                  QString nameLeft, QString regionLeft, QString nameRight, QString regionRight,
                  QImage leftFlag, QImage rightFlag,
                  bool isForJudge, bool showAdvertisement);

    ~FightingTable();

private slots:
    void updateInfo();

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent * e);


};

#endif // FIGHTING_TABLE_H
