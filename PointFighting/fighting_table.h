#ifndef FIGHTING_TABLE_H
#define FIGHTING_TABLE_H

#include <QWidget>
#include <QDialog>
#include <QSound>
#include <QCloseEvent>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <chrono>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include <QMessageBox>
#include "ui_fighting_table.h"
#include "ui_form.h"
#include "formscore.h"
#include "fighting.h"
#include <QtGui>

#include <QMessageBox>
#include "ui_fighting_table.h"
#include "ui_form.h"
#include "dialogdisq.h"
#include "formscore.h"
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <qmessagebox.h>
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
    QPushButton *pushButtonStart;
    QPushButton *pushButtonDoctor;
    QPushButton *pushButtonStop;

    const int poolTime = 250;
    const QString nameLeft;
    const QString nameRight;
    const QImage mLeftFlag;
    const QImage mRightFlag;

    QVector<FormScore*> left, right;
    QVector<FightingTable*> allTables;
    const bool dialogForJudge;
    const bool showAdvertisement;

    QString forceResult;

public:

    FightingTable(Fighting *f,
                  QString nameLeft, QString regionLeft, QString nameRight, QString regionRight,
                  QImage leftFlag, QImage rightFlag,
                  bool dialogForJudge, bool showAdvertisement);

//    ~FightingTable(){
//        delete ui;
//        for (FightingTable* f : allTables)
//            if (f != this)
//                delete f;
//    }

private:
    static QString getTimeMMSS(long long time);


private slots:
    void updateInfo();

protected:
    void closeEvent(QCloseEvent *event);


};

#endif // FIGHTING_TABLE_H
